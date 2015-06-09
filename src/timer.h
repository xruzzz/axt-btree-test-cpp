/**
	Created on	: 26 мая 2015 г.
	Таймер для измерения времени выполнения
*/

#ifndef TIMER_H_
#define TIMER_H_
//#define LINUX

#include <stdio.h>
#include <stdlib.h>

#ifdef LINUX

typedef long long LONGLONG;
typedef union _LARGE_INTEGER {
  struct {
	unsigned long LowPart;
    long HighPart;
  };
  struct {
	unsigned long LowPart;
    long HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

#else
#include <Windows.h>
#endif

#if _MSC_VER > 1000
#pragma once
#endif

class Timer
{
   public:

      Timer()
      {
#ifndef LINUX
         if (!m_llFrequency)
         {
            LARGE_INTEGER  liFrequency;

            QueryPerformanceFrequency(&liFrequency);

            m_llFrequency = liFrequency.QuadPart;

         }

         QueryPerformanceCounter(&m_llCounter);
#endif
      }

      unsigned long getTicks()
      {
#ifdef LINUX
         unsigned long x;
         __asm__ volatile ("rdtsc\n\tshl $32, %%rdx\n\tor %%rdx, %%rax" : "=a" (x) : : "rdx");
         return x;
#else
   	  LARGE_INTEGER liNow;

        QueryPerformanceCounter(&liNow);

        return (unsigned long)(liNow.QuadPart - m_llCounter.QuadPart) / m_llFrequency;
#endif
      }

   private:
      LARGE_INTEGER  m_llCounter;
      static LONGLONG   m_llFrequency;

   private:

      Timer(const Timer&);
      Timer& operator=(const Timer&);
};

#endif
