/* Delay in seconds between queries. */
static const int DELAY = 10;

/* Show notification when the current percent is lower than... */
static const int WARN_PERCENT = 16;

/*
 * Set notification urgency level.
 * NOTIFY_URGENCY_LOW
 * NOTIFY_URGENCY_NORMAL
 * NOTIFY_URGENCY_CRITICAL
 */
static const NotifyUrgency URGENCY_LEVEL = NOTIFY_URGENCY_CRITICAL;

/* 
 * Set notification timeout in milliseconds.
 * Or you can use one of the following constants...
 * NOTIFY_EXPIRES_DEFAULT
 * NOTIFY_EXPIRES_NEVER
 */
static const gint TIMEOUT = NOTIFY_EXPIRES_DEFAULT;

/* Define your battery here. Check /sys/class/power_supply */
static const char *BAT_PATH = "/sys/class/power_supply/BAT0";
