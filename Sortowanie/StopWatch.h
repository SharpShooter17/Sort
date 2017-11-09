#pragma once

#ifdef __FreeBSD__
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/resource.h>
	#define TO_MS_DIVISOR (1000)
#else
	#include <ctime>
	#define TO_MS_DIVISOR (CLOCKS_PER_SEC / 1000)
#endif

/*
 * timeHandler.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

class CStopWatch
{
	float start, last, mem;

public:
	CStopWatch()
		: start(clock())
	{
		last=clock();
		mem=0;
	}

	float getDiff() //get diff in milliseconds
	{
		float ret = clock() - last;
		last = clock();
		return ret / TO_MS_DIVISOR;
	}
	void update()
	{
		last=clock();
	}
	void remember()
	{
		mem=clock();
	}
	float memDif()
	{
		return (clock()-mem) / TO_MS_DIVISOR;
	}

	float GetElapsedSeconds()
    {
        update();
        return getDiff() * 1000;
    }

    void Reset()
    {
        last=clock();
		mem=0;
    }


private:
	float clock()
	{
	#ifdef __FreeBSD__
		struct rusage usage;
		getrusage(RUSAGE_SELF, &usage);
		return static_cast<si64>(usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) * 1000000 + usage.ru_utime.tv_usec + usage.ru_stime.tv_usec;
	#else
		return std::clock();
	#endif
	}
};
