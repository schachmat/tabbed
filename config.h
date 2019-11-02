/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "DejaVu Sans Mono:pixelsize=16:antialias=false:autohint=false";
static const char* normbgcolor  = "#073642";
static const char* normfgcolor  = "#93a1a1";
static const char* selbgcolor   = "#586e75";
static const char* selfgcolor   = "#eee8d5";
static const char* urgbgcolor   = "#073642";
static const char* urgfgcolor   = "#dc322f";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "…";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 0;
static Bool npisrelative  = True;

#define SETPROP(p) { \
	.v = (char *[]){ "/bin/sh", "-c", \
		"prop=\"`xwininfo -children -id $1 | grep '^     0x'" \
		" | sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@'" \
		" | tac - \"${HOME}/.$2/history\"" \
		" | awk '!x[$0]++'" \
		" | xargs -0 printf %b | dmenu -i -l 10`\"" \
		" && xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
		p, winid, clientbin, NULL \
	} \
}

#define MODKEY Mod4Mask
static Key keys[] = {
	/* modifier              key            function     argument */
	{ MODKEY,                XK_z,          focusonce,   { 0 } },
	{ MODKEY,                XK_z,          spawn,       { 0 } },

	{ MODKEY,                XK_adiaeresis, rotate,      { .i = +1 } },
	{ MODKEY,                XK_odiaeresis, rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,      XK_odiaeresis, movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,      XK_adiaeresis, movetab,     { .i = +1 } },

	{ ControlMask,           XK_Tab,        rotate,      { .i = +1 } },
	{ ControlMask|ShiftMask, XK_Tab,        rotate,      { .i = -1 } },
	{ ControlMask|ShiftMask, XK_Page_Up,    movetab,     { .i = -1 } },
	{ ControlMask|ShiftMask, XK_Page_Down,  movetab,     { .i = +1 } },

	{ MODKEY,                XK_f,          rotate,      { .i = 0 } },

	{ MODKEY,                XK_p,          spawn,       SETPROP("_TABBED_SELECT_TAB") },

	{ MODKEY,                XK_udiaeresis, killclient,  { 0 } },
	{ ControlMask,           XK_F4,         killclient,  { 0 } },
};
