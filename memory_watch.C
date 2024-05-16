#include <stdio.h>
#include <stdlib.h>

size_t getPeakRSS();
size_t getCurrentRSS();

size_t getPeakRSS(){

// I don't think we need this...
#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
    struct psinfo psinfo;
    int fd = -1;
    if ((fd = open("/proc/self/psinfo", O_RDONLY)) == -1)
        return (size_t)0L;
    if (read(fd, &psinfo, sizeof(psinfo)) != sizeof(psinfo)){
        close(fd);
        return (size_t)0L;
    }
    close(fd);
    return (size_t)(psinfo.pr_rssize * 1024L);

#elif defined(__unix__) || defined(__unix) || defined(unix)
    struct rusage rusage;
    getrusage(RUSAGE_SELF, &rusage);

#else
    return (size_t)(rusage.ru_maxrss * 1024L);
#endif

}

size_t getCurrentRSS(){

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    long rss = 0L;
    FILE *fp = NULL;
    
    if ((fp = fopen("/proc/self/statm", "r")) == NULL)
        return (size_t)0L;
        
    if (fscanf(fp, "%*s%ld", &rss) != 1){
        fclose(fp);
        return (size_t)0L;
    }
    
    fclose(fp);
    return (size_t)rss * (size_t)sysconf(_SC_PAGESIZE);

#else
    return (size_t)0L;
#endif

}
