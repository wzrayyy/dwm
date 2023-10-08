/* appearance */
static const unsigned int borderpx    = 2;
static const unsigned int snap        = 0;
static const unsigned int gappih      = 20;
static const unsigned int gappiv      = 10;
static const unsigned int gappoh      = 10;
static const unsigned int gappov      = 10;
static int smartgaps                  = 1;
static const int showbar              = 1;
static const int topbar               = 1;
static const char *fonts[]            = { "Mononoki Nerd Font:size=12", "Noto Color Emoji:size=11" };
static const char dmenufont[]         = "Mononoki Nerd Font:size=12";
static const char col_gray1[]         = "#222222";
static const char col_gray2[]         = "#444444";
static const char col_gray3[]         = "#bbbbbb";
static const char col_gray4[]         = "#eeeeee";
static const char col_accent[]        = "#db8402";
static const unsigned int baralpha    = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2, col_accent  },
};

static const unsigned int alphas[][3] = {
	/*               fg      bg        border*/
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance  name                  tags mask  isfloating  monitor */
	{ "Firefox",   NULL,     "Picture-in-Picture", 0,         1,          -1 },
};


/* layout(s) */
static const float mfact = 0.60;
static const int nmaster = 1;
static const int resizehints = 1;
static const int lockfullscreen = 1;
int spawnmaster = 0;

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol  reverse  function */
        { "[/]",   "[\\]",  dwindle},
	{ "[]=",   "=[]",   tile },
	{ "[M]",   "[M]",   monocle },
	{ "><>",   "<><",   NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,		KEY,      tagview,        {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,		KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggleview,     {.ui = 1 << TAG} }, \

#define SHCMD(...) { .v = (const char*[]){ __VA_ARGS__, NULL } }

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier           key        function        argument */
	// movement
	{ MODKEY,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             XK_b,      togglebar,      {0} },
	{ MODKEY,             XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,             XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_l,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_c,      zoom,           {0} },
	{ MODKEY,             XK_Tab,    view,           {0} },
	{ MODKEY,             XK_q,      killclient,     {0} },

	// layout
	{ MODKEY,             XK_y,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,             XK_u,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,   XK_f,      togglefloating, {0} },
	{ MODKEY|ShiftMask,   XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,             XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,             XK_p,      invertdir,      {0} },

	// apps
	{ MODKEY,             XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY,             XK_t,      spawn,          SHCMD("telegram-desktop") },
	{ MODKEY|ShiftMask,   XK_s,      spawn,          SHCMD("flameshot", "gui") },
	{ MODKEY,             XK_i,      spawn,          SHCMD("dunstctl", "history-pop") },
	{ MODKEY,             XK_o,      spawn,          SHCMD("dunstctl", "close") },
	{ MODKEY,             XK_x,      spawn,          SHCMD("discord") },

	// tags
	TAGKEYS(              XK_1,                      0)
	TAGKEYS(              XK_2,                      1)
	TAGKEYS(              XK_3,                      2)
	TAGKEYS(              XK_4,                      3)
	TAGKEYS(              XK_5,                      4)
	TAGKEYS(              XK_6,                      5)
	TAGKEYS(              XK_7,                      6)
	TAGKEYS(              XK_8,                      7)
	TAGKEYS(              XK_9,                      8)
	{ MODKEY|ShiftMask,   XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click              event mask      button          function        argument */
	{ ClkLtSymbol,        0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,        0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,        0,              Button2,        zoom,           {0} },
	{ ClkStatusText,      0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,       MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,       MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,       MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,          0,              Button1,        view,           {0} },
	{ ClkTagBar,          0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,          MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,          MODKEY,         Button3,        toggletag,      {0} },
};

