/* appearance */
#include <X11/X.h>
#include <X11/Xutil.h>
static const unsigned int borderpx	  = 2;
static const unsigned int snap        	  = 0;
static const unsigned int swallowfloating = 0;
static const unsigned int gappih          = 20;
static const unsigned int gappiv          = 10;
static const unsigned int gappoh          = 10;
static const unsigned int gappov          = 10;
static int smartgaps                      = 1;
static const int showbar                  = 1;
static const int topbar                   = 1;
static const char *fonts[]                = { "Mononoki Nerd Font:size=12", "Noto Color Emoji:size=11" };
static const char dmenufont[]             = "Mononoki Nerd Font:size=12";
static const char col_gray1[]             = "#3a3a3a";
static const char col_gray2[]             = "#5c5c5c";
static const char col_gray3[]             = "#bbbbbb";
static const char col_gray4[]             = "#eeeeee";
static const char col_accent[]            = "#db8402";
static const unsigned int baralpha        = 0xd0;
static const unsigned int borderalpha     = OPAQUE;

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
static const unsigned int nerdfont_icons = (1 << 8) | (1 << 7);
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "", "" };
static const char *metaworkspaces[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance  title			 tags_mask  isfloating  isterminal  noswallow monitor */
	{ "Firefox",	NULL,	  "Picture-in-Picture",  0,         1,		0,	    1,	      -1 },
	{ "copyq",     	NULL,     NULL,		         0,         1,          0,	    0,        -1 },
	{ "Alacritty",	NULL,	  NULL,	                 0,         0,          1,	    0,        -1 },
	{ "floating",	NULL, 	  NULL,	                 0,         1,          0,	    0,        -1 },
};


/* layout(s) */
static const float mfact = 0.60;
static const int nmaster = 1;
static const int resizehints = 1;
static const int lockfullscreen = 1;
static const int spawnmaster = 0;

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol  reverse  function */
	{ "[]=",   "=[]",   tile },
        { "[/]",   "[\\]",  dwindle},
	{ "[M]",   "[M]",   monocle },
	{ "><>",   "<><",   NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,					KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             		KEY,      tagview,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           		KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,				KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, 		KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ControlMask,			KEY,	  tagmetaws,      {.i = TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask|ControlMask,	KEY,	  tagviewmetaws,  {.i = TAG} },

#define SHCMD(...) { .v = (const char*[]){ __VA_ARGS__, NULL } }

/* commands */
static char dmenumon[2] = "0";
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier           key        function        argument */
	// movement
	// { MODKEY|ShiftMask,   XK_l,      incnmaster,     {.i = +1 } },
	// { MODKEY|ShiftMask,   XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_d,		spawn,			{.v = dmenucmd } },
	{ MODKEY,			XK_Return, 	spawn,          	{.v = termcmd } },
	{ MODKEY|ShiftMask,   		XK_b,      	togglebar,      	{0} },
	{ MODKEY,             		XK_j,      	focusstack,     	{.i = +1 } },
	{ MODKEY,             		XK_k,      	focusstack,     	{.i = -1 } },
	{ MODKEY,			XK_n,      	setmfact,       	{.f = -0.05} },
	{ MODKEY,		        XK_m,      	setmfact,       	{.f = +0.05} },
	{ MODKEY,		        XK_c,      	zoom,           	{0} },
	{ MODKEY,		        XK_q,      	killclient,     	{0} },

	// layout
	{ MODKEY|ControlMask,	        XK_u,      	setlayout,      	{.v = &layouts[0]} },
	{ MODKEY|ControlMask|ShiftMask, XK_u,      	setlayout,      	{.v = &layouts[1]} },
	{ MODKEY|ControlMask,		XK_m,      	setlayout,      	{.v = &layouts[2]} },
	{ MODKEY|ControlMask|ShiftMask, XK_m,      	setlayout,      	{.v = &layouts[3]} },
	{ MODKEY,		        XK_f,      	togglefullscr,  	{0} },
	{ MODKEY|ShiftMask,		XK_f,      	togglefloating,		{0} },
	{ MODKEY|ShiftMask,   		XK_j,      	movestack,      	{.i = +1 } },
	{ MODKEY|ShiftMask,   		XK_k,      	movestack,      	{.i = -1 } },
	{ MODKEY,             		XK_0,      	view,           	{.ui = ~0 } },
	{ MODKEY|ControlMask, 		XK_0,      	tag,            	{.ui = ~0 } },
	{ MODKEY|ControlMask, 		XK_p,      	invertdir,      	{0} },

	// metaws
	{ MODKEY|Mod1Mask,	 	XK_i,		traversemetaws,      	{.i = +1} },
	{ MODKEY|Mod1Mask,	 	XK_u,		traversemetaws,      	{.i = -1} },
	{ MODKEY|Mod1Mask,		XK_m,		tagmetaws,      	{.i = -1} },
	{ MODKEY|ControlMask|Mod1Mask,	XK_i,		moveviewmetaws,      	{.i = +1} },
	{ MODKEY|ControlMask|Mod1Mask,	XK_u,		moveviewmetaws,      	{.i = -1} },

	{ MODKEY|ShiftMask|ControlMask|Mod1Mask,	XK_i,		movemetaws,      	{.i = +1} },
	{ MODKEY|ShiftMask|ControlMask|Mod1Mask,	XK_u,		movemetaws,      	{.i = -1} },

	// apps
	{ MODKEY,             		XK_w,		spawn,          	SHCMD("firefox") },
	{ MODKEY|ShiftMask,    		XK_p,      	spawn,          	SHCMD("cast") },
	{ MODKEY,             		XK_t,      	spawn,          	SHCMD("ayugram-desktop") },
	{ MODKEY|ShiftMask,   		XK_s,      	spawn,          	SHCMD("flameshot", "gui") },
	{ MODKEY,             		XK_i,      	spawn,          	SHCMD("dunstctl", "history-pop") },
	{ MODKEY,             		XK_o,      	spawn,          	SHCMD("dunstctl", "close") },
	{ MODKEY|ControlMask,  		XK_i,      	spawn,          	SHCMD("dunstctl", "set-paused", "false") },
	{ MODKEY|ControlMask,  		XK_o,      	spawn,          	SHCMD("dunstctl", "set-paused", "true") },
	{ MODKEY|ShiftMask,   		XK_r,      	spawn,          	SHCMD("xr") },
	{ MODKEY,             		XK_x,      	spawn,          	SHCMD("vesktop") },
	{ MODKEY|ControlMask, 		XK_v,      	spawn,          	SHCMD("vpn", "-d", "--visual") },
	{ MODKEY|ShiftMask,   		XK_v,      	spawn,          	SHCMD("vpn", "--visual") },

	// tags
	TAGKEYS(              		XK_1,		                	0)
	TAGKEYS(              		XK_2,      	                	1)
	TAGKEYS(              		XK_3,      	                	2)
	TAGKEYS(              		XK_4,      	                	3)
	TAGKEYS(              		XK_5,      	                	4)
	TAGKEYS(              		XK_6,      	                	5)
	TAGKEYS(              		XK_7,      	                	6)
	TAGKEYS(              		XK_8,      	                	7)
	TAGKEYS(              		XK_9,      	                	8)
	{ MODKEY|ShiftMask,   		XK_q,      	quit,           	{0} },
	{ MODKEY,             		XK_h,      	focusmon,       	{.i = -1 } },
	{ MODKEY,             		XK_l,      	focusmon,       	{.i = +1 } },
	{ MODKEY|ControlMask, 		XK_h,      	tagmon,         	{.i = -1 } },
	{ MODKEY|ControlMask, 		XK_l,      	tagmon,         	{.i = +1 } },
	{ MODKEY|ShiftMask,   		XK_h,      	focustagmon,    	{.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_l,      	focustagmon,    	{.i = +1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, ClkRootWin, or ClkMetaWorkspace */
static const Button buttons[] = {
	/* click		event mask		button		function	argument */
	{ ClkClientWin,		MODKEY,                 Button1,        movemouse,      {0} },
	{ ClkClientWin,		MODKEY,                 Button2,        togglefloating, {0} },
	{ ClkClientWin,		MODKEY,                 Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY|ControlMask,     Button1,        resizemouse,    {0} },
	{ ClkTagBar,   		0,                      Button3,        toggleview,     {0} },
	{ ClkTagBar,   		MODKEY,                 Button3,        toggletag,      {0} },

	{ ClkTagBar,		0,                      Button1,	view,           {0} },
	{ ClkTagBar,		ShiftMask,              Button1,        tagview,        {0} },
	{ ClkTagBar,		ControlMask,            Button1,        tag,            {0} },
	{ ClkTagBar,		Mod1Mask,		Button1,        toggletag,      {0} },
	{ ClkTagBar,		ControlMask|ShiftMask,  Button1,        toggleview,     {0} },

	{ ClkMwSymbol,		0,			Button1,        traversemetaws, {.i = +1} },
	{ ClkMwSymbol,		0,			Button3,        traversemetaws, {.i = -1} },
};
