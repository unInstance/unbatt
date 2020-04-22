# unbatt
Bloat-free program that sends notifications if your battery is low.

# USAGE
Clone this repository and enter it:

```
git clone https://github.com/unInstance/unbatt
cd unbatt
```

Make sure the last line in `config.h` points to the battery you need.
Specify the path to one from `/sys/class/power_supply`

Optional: adjust other settings in `config.h`

Compile and install unbatt:

```
make
sudo make install
```

Ascertain that `/usr/local/bin` is in your `PATH` variable.

Add the following in your `~/.xinitrc`:

```
unbatt &
```

Restart X11.

### Before you put this at work
Prior to putting this into `~/.xinitrc`, start unbatt in a terminal window to see whether there is any output. If there is not, then the program works fine.

# LICENSE
Copyright 2020 Ivan Kovmir

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

# NOTES
Back in the day when was an unskilled Arch user, right after I had installed dwm, I was looking for a program to display notifications if ... Well, you got me. It turned out there were a lot of such things but all of them were either bloated, or did not work at all. Use this code if you feel the way I do.
