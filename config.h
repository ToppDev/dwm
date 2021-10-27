/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 3;         /* border pixel of windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const unsigned int gappih    = 20;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;        /* vert inner gap between windows */
static const unsigned int gappoh    = 10;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;        /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;         /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;    /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;    /* systray spacing */
static const int systraypinningfailfirst = 1;    /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;         /* 0 means no systray */
static const int swallowfloating    = 0;         /* 1 means swallow floating windows by default */
static const int showbar            = 1;         /* 0 means no bar */
static const int topbar             = 1;         /* 0 means bottom bar */
static const int viewontag          = 1;         /* Switch view on tag switch */
static const char *fonts[]          = { "Inconsolata Nerd Font:size=13", "JoyPixels:pixelsize=13:antialias=true:autohint=true" };
static const char normbgcolor[]     = "#222222";
static const char normbordercolor[] = "#444444";
static const char normfgcolor[]     = "#bbbbbb";
static const char selfgcolor[]      = "#eeeeee";
static const char selbordercolor[]  = "#770000";
static const char selbgcolor[]      = "#005577";

enum { SchemeNorm,  SchemeSel,   SchemeCol0,  SchemeCol1,  SchemeCol2,  SchemeCol3,
       SchemeCol4,  SchemeCol5,  SchemeCol6,  SchemeCol7,  SchemeCol8,  SchemeCol9,
       SchemeCol10, SchemeCol11, SchemeCol12, SchemeCol13, SchemeCol14, SchemeCol15,
       SchemeCol16, SchemeCol17, SchemeCol18  }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg            bg           border   */
	[SchemeNorm]  = { normfgcolor, normbgcolor, normbordercolor }, // \x0b
	[SchemeSel]   = { selfgcolor,  selbgcolor,  selbordercolor  }, // \x0c
	[SchemeCol0]  = { "#000000",   normbgcolor, normbordercolor }, // \x0d - black
	[SchemeCol1]  = { "#800000",   normbgcolor, normbordercolor }, // \x0e - maroon
	[SchemeCol2]  = { "#008000",   normbgcolor, normbordercolor }, // \x0f - green
	[SchemeCol3]  = { "#808000",   normbgcolor, normbordercolor }, // \x10 - olive
	[SchemeCol4]  = { "#000080",   normbgcolor, normbordercolor }, // \x11 - navy
	[SchemeCol5]  = { "#800080",   normbgcolor, normbordercolor }, // \x12 - purple
	[SchemeCol6]  = { "#008080",   normbgcolor, normbordercolor }, // \x13 - teal
	[SchemeCol7]  = { "#C0C0C0",   normbgcolor, normbordercolor }, // \x14 - silver
	[SchemeCol8]  = { "#808080",   normbgcolor, normbordercolor }, // \x15 - gray
	[SchemeCol9]  = { "#FF0000",   normbgcolor, normbordercolor }, // \x16 - red
	[SchemeCol10] = { "#00FF00",   normbgcolor, normbordercolor }, // \x17 - lime
	[SchemeCol11] = { "#FFFF00",   normbgcolor, normbordercolor }, // \x18 - yellow
	[SchemeCol12] = { "#0000FF",   normbgcolor, normbordercolor }, // \x19 - blue
	[SchemeCol13] = { "#FF00FF",   normbgcolor, normbordercolor }, // \x1a - magenta
	[SchemeCol14] = { "#00FFFF",   normbgcolor, normbordercolor }, // \x1b - cyan
	[SchemeCol15] = { "#FFFFFF",   normbgcolor, normbordercolor }, // \x1c - white
	[SchemeCol16] = { "#FFA500",   normbgcolor, normbordercolor }, // \x1d - orange
	[SchemeCol17] = { "#FF6347",   normbgcolor, normbordercolor }, // \x1e - tomato
	[SchemeCol18] = { "#adff2f",   normbgcolor, normbordercolor }, // \x1f - lightsalmon
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "octaveclean", "--no-gui", "--silent", "--persist", "--eval", "disp(['GNU Octave, version ' version]);\n", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance     title                       tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Xfce4-appfinder", NULL,        NULL,                       0,         1,          0,           0,        -1 },
	{ "keepassxc",       NULL,        NULL,                       0,         1,          0,           0,        -1 },
	{ "Peek",            NULL,        NULL,                       0,         1,          0,           0,        -1 },
	{ NULL,              NULL,        "Copying",                  0,         1,          0,           0,        -1 },
	{ NULL,              NULL,        "Deleting",                 0,         1,          0,           0,        -1 },
	{ NULL,              NULL,        "Moving",                   0,         1,          0,           0,        -1 },
	{ NULL,              NULL,        "File Operation Progress",  0,         1,          0,           0,        -1 },
	{ NULL,              NULL,        "Save File",                0,         1,          0,           0,        -1 },
	{ TERMCLASS,         NULL,        NULL,                       0,         0,          1,           0,        -1 },
	{ NULL,              NULL,        "Event Tester",             0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,              "spterm",    NULL,                       SPTAG(0),  1,          1,           0,        -1 },
	{ NULL,              "spcalc",    NULL,                       SPTAG(1),  1,          0,           0,        -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                   /* Default: Master on left, slaves on right */
	{ "TTT",      bstack },                 /* Master on top, slaves on bottom */

 	{ "[@]",      spiral },                 /* Fibonacci spiral */
 	{ "[\\]",     dwindle },                /* Decreasing in size right and leftward */

	{ "[D]",      deck },                   /* Master on left, slaves in monocle-like mode on right */
	{ "[M]",      monocle },                /* All windows on top of eachother */

	{ "|M|",      centeredmaster },         /* Master in middle, slaves on sides */
	{ ">M>",      centeredfloatingmaster }, /* Same but master floats */

	{ "><>",      NULL },                   /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key              function        argument */
	// { MODKEY,                    XK_Escape,       spawn,          SHCMD("") },
	{ MODKEY,                       XK_grave,        spawn,          SHCMD("dmenuunicode") },
	TAGKEYS(                        XK_1,                            0)
	TAGKEYS(                        XK_2,                            1)
	TAGKEYS(                        XK_3,                            2)
	TAGKEYS(                        XK_4,                            3)
	TAGKEYS(                        XK_5,                            4)
	TAGKEYS(                        XK_6,                            5)
	TAGKEYS(                        XK_7,                            6)
	TAGKEYS(                        XK_8,                            7)
	TAGKEYS(                        XK_9,                            8)
	{ MODKEY,                       XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,        spawn,          SHCMD("pamixer --allow-boost -d 5" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ MODKEY|ShiftMask,             XK_minus,        spawn,          SHCMD("pamixer --allow-boost -d 15" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ MODKEY,                       XK_equal,        spawn,          SHCMD("pamixer --allow-boost -i 5" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ MODKEY|ShiftMask,             XK_equal,        spawn,          SHCMD("pamixer --allow-boost -i 15" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ MODKEY,                       XK_BackSpace,    spawn,          SHCMD("sysact -n 2") },
	{ MODKEY|ShiftMask,             XK_BackSpace,    spawn,          SHCMD("sysact -n 3") },

	{ MODKEY,                       XK_Tab,          shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_q,            killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,            spawn,          SHCMD("sysact -n 6") },
	{ MODKEY,                       XK_w,            spawn,          SHCMD("$BROWSER") },
	// { MODKEY,                    XK_e,            spawn,          SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") },
	// { MODKEY|ShiftMask,          XK_e,            spawn,          SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
	{ MODKEY,                       XK_r,            spawn,          SHCMD(TERMINAL " -e htop") },
	{ MODKEY,                       XK_t,            setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,             XK_t,            setlayout,      {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,                       XK_y,            setlayout,      {.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,             XK_y,            setlayout,      {.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,                       XK_u,            setlayout,      {.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,             XK_u,            setlayout,      {.v = &layouts[5]} }, /* monocle */
	{ MODKEY,                       XK_i,            setlayout,      {.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,             XK_i,            setlayout,      {.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,                       XK_o,            incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,            incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_p,            spawn,          SHCMD("playerctl play-pause || mpc toggle") },
	{ MODKEY,                       XK_bracketleft,  spawn,          SHCMD("playerctl previous || mpc prev") },
	{ MODKEY|ShiftMask,             XK_bracketleft,  spawn,          SHCMD("playerctl position 15- || mpc seek -15") },
	{ MODKEY,                       XK_bracketright, spawn,          SHCMD("playerctl next || mpc next") },
	{ MODKEY|ShiftMask,             XK_bracketright, spawn,          SHCMD("playerctl position 15+ || mpc seek +15") },
	// { MODKEY,                    XK_backslash,    spawn,          SHCMD("") },

	{ MODKEY,                       XK_a,            togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_a,            defaultgaps,    {0} },
	{ MODKEY,                       XK_s,            togglesticky,   {0} },
	{ MODKEY,                       XK_d,            spawn,          SHCMD("j4-dmenu-desktop") },
	{ MODKEY|ShiftMask,             XK_d,            spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_f,            togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,            setlayout,      {.v = &layouts[8]} },
	// { MODKEY,                    XK_g,            spawn,          SHCMD("") },
	{ MODKEY,                       XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,            spawn,          SHCMD("sysact -n 1") },
	{ MODKEY,                       XK_semicolon,    togglescratch,  {.ui = 0} },
	{ MODKEY,                       XK_apostrophe,   togglescratch,  {.ui = 1} },
	{ MODKEY,                       XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,       spawn,          SHCMD("thunar") },

	{ MODKEY,                       XK_z,            incrgaps,       {.i = +3 } },
	{ MODKEY|ShiftMask,             XK_z,            incrgaps,       {.i = -3 } },
	{ MODKEY,                       XK_x,            spawn,          SHCMD("keepassxc") },
	{ MODKEY,                       XK_c,            zoom,           {0} },
	// { MODKEY,                    XK_v,            spawn,          SHCMD("") },
	{ MODKEY,                       XK_b,            togglebar,      {0} },
	{ MODKEY,                       XK_n,            spawn,          SHCMD("joplin-desktop") },
	{ MODKEY,                       XK_m,            spawn,          SHCMD("spotify") },
	{ MODKEY|ShiftMask,             XK_m,            spawn,          SHCMD("pamixer --toggle-mute" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ MODKEY,                       XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,       tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_space,        zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,        togglefloating, {0} },

	{ MODKEY,                       XK_Left,         spawn,          SHCMD("variety --previous") },
	{ MODKEY,                       XK_Right,        spawn,          SHCMD("variety --next") },
	{ MODKEY|ShiftMask,             XK_Up,           spawn,          SHCMD("variety --move-to-favorites") },
	{ MODKEY|ShiftMask,             XK_Down,         spawn,          SHCMD("variety --trash") },

	// { MODKEY,                    XK_Insert,       spawn,          SHCMD("xdotool type $(grep -v '^#' ~/.local/share/talis/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
	{ MODKEY,                       XK_Delete,       spawn,          SHCMD("xkill") },
	// { MODKEY,                    XK_Home,         spawn,          SHCMD("") },
	// { MODKEY,                    XK_End,          spawn,          SHCMD("") },
	// { MODKEY,                    XK_Page_Up,      spawn,          SHCMD("") },
	// { MODKEY,                    XK_Page_Down,    spawn,          SHCMD("") },

	// { MODKEY,                    XK_F1,           spawn,          SHCMD("") },
	// { MODKEY,                    XK_F2,           spawn,          SHCMD("") },
	{ MODKEY,                       XK_F3,           spawn,          SHCMD("xfce4-appfinder") },
	{ MODKEY,                       XK_F4,           spawn,          SHCMD(TERMINAL " -e pulsemixer" /* "; kill -44 $(pidof dwmblocks)" */) },
	// { MODKEY,                    XK_F5,           spawn,          SHCMD("") },
	// { MODKEY,                    XK_F6,           spawn,          SHCMD("") },
	// { MODKEY,                    XK_F7,           spawn,          SHCMD("") },
	// { MODKEY,                    XK_F8,           spawn,          SHCMD("") },
	// { MODKEY,                    XK_F9,           spawn,          SHCMD("") },
	// { MODKEY,                    XK_F10,          spawn,          SHCMD("") },
	// { MODKEY,                    XK_F11,          spawn,          SHCMD("") },
	{ MODKEY,                       XK_F12,          spawn,          SHCMD("displayselect") },

	{ 0,                            XK_Print,        spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_Scroll_Lock,  spawn,          SHCMD("killall screenkey || screenkey &") },
	// { MODKEY,                    XK_Pause,        spawn,          SHCMD("") },

	{ 0,                   XF86XK_AudioMute,         spawn,          SHCMD("pamixer --toggle-mute" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ 0,                   XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pamixer --allow-boost -i 3" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ 0,                   XF86XK_AudioLowerVolume,  spawn,          SHCMD("pamixer --allow-boost -d 3" /* "; kill -44 $(pidof dwmblocks)" */) },
	{ 0,                   XF86XK_AudioPrev,         spawn,          SHCMD("playerctl previous || mpc prev") },
	{ 0,                   XF86XK_AudioNext,         spawn,          SHCMD("playerctl next || mpc next") },
	{ 0,                   XF86XK_AudioPause,        spawn,          SHCMD("playerctl play-pause || mpc toggle") },
	{ 0,                   XF86XK_AudioPlay,         spawn,          SHCMD("playerctl play-pause || mpc toggle") },
	{ 0,                   XF86XK_AudioStop,         spawn,          SHCMD("playerctl stop || mpc stop") },
	{ 0,                   XF86XK_AudioRewind,       spawn,          SHCMD("playerctl position 10- || mpc seek -10") },
	{ 0,                   XF86XK_AudioForward,      spawn,          SHCMD("playerctl position 10+ || mpc seek +10") },
	{ 0,                   XF86XK_AudioMedia,        spawn,          SHCMD("spotify") },
	{ 0,                   XF86XK_AudioMicMute,      spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0,                   XF86XK_PowerOff,          spawn,          SHCMD("sysact -n 2") },
	{ 0,                   XF86XK_Calculator,        togglescratch,  {.ui = 1} },
	{ 0,                   XF86XK_DOS,               spawn,          SHCMD(TERMINAL) },
	{ 0,                   XF86XK_Sleep,             spawn,          SHCMD("syssleep") },
	{ 0,                   XF86XK_HomePage,          spawn,          SHCMD("$BROWSER") },
	{ 0,                   XF86XK_LogOff,            spawn,          SHCMD("lockscreen") },
	{ 0,                   XF86XK_ScreenSaver,       spawn,          SHCMD("lockscreen & xset dpms force off; playerctl pause || mpc pause && pauseallmpv") },
	{ 0,                   XF86XK_TaskPane,          spawn,          SHCMD(TERMINAL " -e htop") },
	{ 0,                   XF86XK_Mail,              spawn,          SHCMD("thunderbird") },
	{ 0,                   XF86XK_MyComputer,        spawn,          SHCMD("thunar") },
	// { 0,                   XF86XK_Battery,           spawn,          SHCMD("") },
	{ 0,                   XF86XK_TouchpadToggle,    spawn,          SHCMD("touchpadtoggle") },
	{ 0,                   XF86XK_MonBrightnessUp,   spawn,          SHCMD("xbacklight -inc 15") },
	{ 0,                   XF86XK_MonBrightnessDown, spawn,          SHCMD("xbacklight -dec 15") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        ShiftMask,      Button2,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button3,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,    {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

// static Button buttons[] = {
// 	/* click                event mask      button          function        argument */
// #ifndef __OpenBSD__
// 	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
// 	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
// 	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
// 	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
// 	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
// 	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
// #endif
// 	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },

// 	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
// 	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
// 	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
// 	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
// 	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
// 	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
// };