/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 3;             /* border pixel of windows */
static unsigned int snap      = 32;            /* snap pixel */
static unsigned int gappih    = 20;            /* horiz inner gap between windows */
static unsigned int gappiv    = 10;            /* vert inner gap between windows */
static unsigned int gappoh    = 10;            /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;            /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;             /* 1 means no outer gap when there is only one window */
static unsigned int systraypinning = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static unsigned int systrayonleft  = 0;        /* 0: systray in the right corner, >0: systray on left of status text */
static unsigned int systrayspacing = 2;        /* systray spacing */
static const int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static int showsystray        = 1;             /* 0 means no systray */
static int swallowfloating    = 0;             /* 1 means swallow floating windows by default */
static int showbar            = 1;             /* 0 means no bar */
static int topbar             = 1;             /* 0 means bottom bar */
static int viewontag          = 1;             /* Switch view on tag switch */
static char *fonts[]          = { "monospace:size=10" };
static char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#770000";
static char selbgcolor[]      = "#005577";
static char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance     title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,        NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,        NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,        NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,        "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,      "spterm",    NULL,           SPTAG(0),  1,          1,           0,        -1 },
	{ NULL,      "spfm",      NULL,           SPTAG(1),  1,          1,           0,        -1 },
	{ NULL,      "keepassxc", NULL,           SPTAG(2),  0,          0,           0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55;       /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;          /* number of clients in master area */
static int resizehints = 0;          /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                   /* Default: Master on left, slaves on right */
	{ "TTT",      bstack },                 /* Master on top, slaves on bottom */

	{ "[M]",      monocle },                /* All windows on top of eachother */
	{ "[D]",      deck },                   /* Master on left, slaves in monocle-like mode on right */

 	{ "[@]",      spiral },                 /* Fibonacci spiral */
 	{ "[\\]",     dwindle },                /* Decreasing in size right and leftward */

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "borderpx",           INTEGER, &borderpx },
		{ "snap",               INTEGER, &snap },
		{ "gappih",             INTEGER, &gappih },
		{ "gappiv",             INTEGER, &gappiv },
		{ "gappoh",             INTEGER, &gappoh },
		{ "gappov",             INTEGER, &gappov },
		{ "smartgaps",          INTEGER, &smartgaps },
		{ "systraypinning",     INTEGER, &systraypinning },
		{ "systrayonleft",      INTEGER, &systrayonleft },
		{ "systrayspacing",     INTEGER, &systrayspacing },
		{ "showsystray",        INTEGER, &showsystray },
		{ "swallowfloating",    INTEGER, &swallowfloating },
		{ "showbar",            INTEGER, &showbar },
		{ "topbar",             INTEGER, &topbar },
		{ "viewontag",          INTEGER, &viewontag },
		// { "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "color0",             STRING,  &normbgcolor },
		{ "color0",             STRING,  &normbordercolor },
		{ "color4",             STRING,  &normfgcolor },
		{ "color0",             STRING,  &selfgcolor },
		{ "color8",             STRING,  &selbordercolor },
		{ "color4",             STRING,  &selbgcolor },
		{ "mfact",              FLOAT,   &mfact },
		{ "nmaster",            INTEGER, &nmaster },
		{ "resizehints",        INTEGER, &resizehints },
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	// { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	// { MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[5]} },
	// { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[6]} },
	// { MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	// { MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_y,      togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_u,      togglescratch,  {.ui = 1 } },
	{ MODKEY,                       XK_x,      togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

