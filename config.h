#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizbadbar        = 0;        /* These add padding around the text in the bar */
static const int vertpadbar         = 2;
static const char *fonts[]          = { "monospace:size=10", "Font Awesome 5 Free Regular:size=12", "Font Awesome 5 Brands:size=12" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#2b203c";  // dark purple
static const char col_gray2[]       = "#444444";  // grey
static const char col_gray3[]       = "#f8f4c0";  // off white
static const char col_gray4[]       = "#ffa000";  // deep yellow
static const char col_cyan[]        = "#aa2637";  // bordeau
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance     title       tags mask     isfloating   monitor */
	{ "Gimp",                   NULL,       NULL,         0,            1,           -1 },
	{ "Firefox",                NULL,       NULL,         1 << 8,       0,           -1 },
	{ "Nautilus",               NULL,       NULL,         0,            1,           -1 },
	{ NULL,                     NULL,     "brightness",   0,            1,           -1 },
	{ NULL,                     NULL,     "float-term",   0,            1,           -1 },
        { NULL,                     NULL,     "alsamixer",    0,            1,           -1 },
        { "File-roller",            NULL,       NULL,         0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[|]",      tile },    /* first entry is default */
	{ "[~]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPER Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPER,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPER|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SUPER|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = {"rofi", "-modi", "drun,run", "-show", "drun", "-show-icons"};
static const char *termcmd[]  = { "st", NULL };
static const char *floattermcmd[] = { "st", "-t", "float-term", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *upvol[]   = { "amixer", "set", "Master", "2%+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "2%-",     NULL };
static const char *mutevol[] = { "st", "-e", "alsamixer",  NULL };
static const char *adjbrightness[] = { "adj-brightness", NULL };
static const char *rangercmd[] = { "st", "-e", "ranger", NULL };

/* Add to keys[] array. With 0 as modifier, you are able to use the keys directly. */
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { SUPER,                        XK_p,      spawn,          {.v = roficmd } },
	{ SUPER,                        XK_Return, spawn,          {.v = termcmd } },
	{ SUPER,                        XK_grave,  spawn,          {.v = floattermcmd } },
	{ SUPER,                        XK_w,      spawn,          {.v = browsercmd } },
        { SUPER,                        XK_d,      spawn,          {.v = rangercmd } },
	{ SUPER,                        XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ SUPER,                        XK_q,      killclient,     {0} },
	{ SUPER,                        XK_t,      setlayout,      {.v = &layouts[0]} },
	{ SUPER,                        XK_f,      setlayout,      {.v = &layouts[1]} },
	{ SUPER,                        XK_m,      setlayout,      {.v = &layouts[2]} },
	{ SUPER,                        XK_space,  setlayout,      {0} },
	{ SUPER|ShiftMask,              XK_space,  togglefloating, {0} },
	{ SUPER,                        XK_0,      view,           {.ui = ~0 } },
	{ SUPER|ShiftMask,              XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { SUPER,                        XK_Left,   viewtoleft,     {0} },
        { SUPER,                        XK_Right,  viewtoright,    {0} },
        { SUPER|ShiftMask,             XK_Left,   tagtoleft,      {0} },
        { SUPER|ShiftMask,             XK_Right,  tagtoright,     {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, // Restarts dwm (patch)
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,              XF86XK_AudioMute,        spawn,          {.v = mutevol } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = upvol   } },
        { 0,              XF86XK_MonBrightnessUp,     spawn,       {.v = adjbrightness} },
        { 0,              XF86XK_MonBrightnessDown,   spawn,       {.v = adjbrightness} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         SUPER,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         SUPER,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            SUPER,         Button1,        tag,            {0} },
	{ ClkTagBar,            SUPER,         Button3,        toggletag,      {0} },
};

