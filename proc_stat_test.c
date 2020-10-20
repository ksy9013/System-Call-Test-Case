// The MIT License (MIT)
// 
// Copyright (c) 2016, 2017 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <linux/procstat.h>
#include <stdlib.h>

int main ( int argc, char ** argv )
{
  if( argc < 2 )
  {
    fprintf(stderr, "Error: No pid specified\n");
    fprintf(stderr, "Usage: proc_stat_test [pid]\n");
    exit(-1);
  }

  int pid_max = 0;
  FILE * fd;
  
  fd = fopen("/proc/sys/kernel/pid_max", "r" );
  int ret = fscanf( fd, "%d", &pid_max );
   
  if( ret == -1 )
  {
    perror("ERROR: ");
  }

  fclose( fd );

  int pid = atoi( argv[1] );
  if( pid < 0 || pid > pid_max )
  {
    fprintf(stderr, "Error: Invalid pid specified\n");
    fprintf(stderr, "Error: pid must be between %d and %d\n", 0, pid_max);
    exit(-1);
  }


  struct proc_stat ps;
  memset( &ps, 0, sizeof( struct proc_stat ) ); 

  syscall(549, pid, &ps);

  // \TODO Fix the other 64-bit numbers
  
  printf("Process State: \n" );
  printf("PID : %d\n", ps.pid );
  printf("PPID: %d\n", ps.parent_pid );
  printf("user_time: %ld\n", ps.user_time );
  printf("sys_time: %ld\n", ps.sys_time );
  printf("state: %ld\n", ps.state );
  printf("time_slice: %d\n", ps.time_slice );
  printf("policy: %d\n", ps.policy );
  printf("priority: %ld\n", ps.priority );
  printf("static priority: %ld\n", ps.static_priority );
  printf("normal priority: %ld\n", ps.normal_priority );
  printf("rt priority: %ld\n", ps.rt_priority );
  printf("num_context_switches: %ld\n", ps.num_context_switches );
  printf("name: %s\n", ps.name );

  return 0;
}
