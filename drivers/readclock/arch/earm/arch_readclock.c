#include <minix/syslib.h>
#include <minix/drvlib.h>
#include <minix/sysutil.h>

#include <sys/mman.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <time.h>

#include "omap_rtc.h"
#include "forward.h"
#include "readclock.h"

int
arch_setup(struct rtc *r)
{
#ifdef AM335X
	r->init = omap_rtc_init;
	r->get_time = omap_rtc_get_time;
	r->set_time = omap_rtc_set_time;
	r->pwr_off = omap_rtc_pwr_off;
	r->exit = omap_rtc_exit;
	return OK;
#elif DM37XX
	fwd_set_label("tps65950.1.48");
	r->init = fwd_init;
	r->get_time = fwd_get_time;
	r->set_time = fwd_set_time;
	r->pwr_off = fwd_pwr_off;
	r->exit = fwd_exit;
	return OK;
#else
	return ENOSYS;
#endif
}
