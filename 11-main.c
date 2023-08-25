#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info = INFO_INIT;
    int fd = 2;

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fd)
        : "r"(fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                return 126;
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                return 127;
            }
            return EXIT_FAILURE;
        }
        info.readfd = fd;
    }
    
    populate_env_list(&info);
    read_history(&info);
    int exit_status = hsh(&info, av);
    write_history(&info);
    free_info(&info, 1);
    
    if (!interactive(&info) && info.status)
        exit(info.status);
    
    if (info.err_num == -2)
    {
        if (info.err_num == -1)
            exit(info.status);
        exit(info.err_num);
    }
    
    return exit_status;
}

