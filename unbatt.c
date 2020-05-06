/*
 * Copyright 2020 Ivan Kovmir
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Includes */
#include <errno.h>
#include <fcntl.h>
#include <libnotify/notify.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* Constants */
#define BUF_SIZE 64
#define MAX_PATH 256
#define AC_ONLINE_PATH "/sys/class/power_supply/AC/online"
#define AC_PLUGGED '1'
#define NOTIFY_APP_NAME "unbatt"

#include "config.h"

int
main(void) {
	int acd;
	int batd;
	long int bat_full_hundreth;
	long int bat_curr;
	int bat_curr_percent;
	ssize_t bytes;
	char path[MAX_PATH];
	char buf[BUF_SIZE];
	NotifyNotification *batt_notifcn;

	notify_init(NOTIFY_APP_NAME);
	batt_notifcn = notify_notification_new("Low battery level", buf, NULL);
	notify_notification_set_urgency(batt_notifcn, URGENCY_LEVEL);
	notify_notification_set_timeout(batt_notifcn, TIMEOUT);

	/* Read the battery's full level */
	strncpy(path, BAT_PATH, MAX_PATH-1); /* Save space for the '\0' */
	path[MAX_PATH-1] = '\0';
	strncat(path, "/energy_full", MAX_PATH - strlen(path)-1);
	batd = open(path, O_RDONLY);
	if (batd < 0) {
		fprintf(stderr, "can't open %s: %s\n",
			path, strerror(errno));
		return -1;
	}
	bytes = read(batd, buf, BUF_SIZE);
	if (bytes < 0) {
		fprintf(stderr, "can't read %s: %s\n",
			path, strerror(errno));
		return -1;
	}
	buf[bytes] = '\0';
	/* Save 1/100 of the battery's full value */
	bat_full_hundreth = strtol(buf, NULL, 10) / 100L;
	close(batd);

	/* Open the file with the current battery level */
	strncpy(path, BAT_PATH, MAX_PATH-1);
	path[MAX_PATH - 1] = '\0';
	strncat(path, "/energy_now", MAX_PATH - strlen(path)-1);
	batd = open(path, O_RDONLY);
	if (batd < 0) {
		fprintf(stderr, "can't open %s: %s\n",
			path, strerror(errno));
		return -1;
	}
	/* Open the file with the AC state */
	acd = open(AC_ONLINE_PATH, O_RDONLY);
	if (batd < 0) {
		fprintf(stderr, "can't open %s: %s\n",
			path, strerror(errno));
		return -1;
	}
	for (;; sleep(DELAY)) {
		/* Read the current battery level */
		bytes = read(batd, buf, BUF_SIZE-1);
		lseek(batd, 0, SEEK_SET);
		/*
		 * Make 'buf' a valid string in order to
		 * avoid converting more characters than we have read.
		 */
		buf[bytes] = '\0';
		bat_curr = strtol(buf, NULL, 10);

		bat_curr_percent = (int)(bat_curr / bat_full_hundreth);

		/* Notify if the battery lever is low and AC is unplugged. */
		if (bat_curr_percent < WARN_PERCENT) {
			/* Read the current AC state */
			read(acd, buf, 1);
			lseek(acd, 0, SEEK_SET);
			if (buf[0] != AC_PLUGGED) {
				/*
				 * snprintf is smart as fuck so that it saves space
				 * for the '\0' under the hood.
				 */
				snprintf(buf, BUF_SIZE, "%d%%", bat_curr_percent);
				notify_notification_update(batt_notifcn,
						"Low battery level", buf, NULL);
				notify_notification_show(batt_notifcn, NULL);
			}
		}
	}
}
