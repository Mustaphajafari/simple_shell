#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: the parameter struct
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exit_status = 0;

    if (info->argv[1])
    {
        int exit_check = _erratoi(info->argv[1]);
        if (exit_check == -1)
        {
            info->status = 2;
            _eputs(info->fname);
            _eputs(": ");
            _eputs(info->argv[1]);
            _eputs(": numeric argument required\n");
            return (1);
        }
        exit_status = _erratoi(info->argv[1]);
    }
    info->err_num = exit_status;
    return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: the parameter struct
 * Return: Always 0
 */
int _mycd(info_t *info)
{
    char buffer[PATH_MAX];
    char *dir = NULL;
    int chdir_ret;

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        dir = _getenv(info, "OLDPWD");
        if (!dir)
        {
            _puts("shell: cd: OLDPWD not set\n");
            return (1);
        }
    }
    else
    {
        dir = info->argv[1];
    }

    if (!dir)
    {
        _puts("shell: cd: HOME not set\n");
        return (1);
    }

    chdir_ret = chdir(dir);
    if (chdir_ret == -1)
    {
        _eputs("shell: cd: ");
        _eputs(dir);
        _eputs(": No such file or directory\n");
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD"));
        _setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
    }
    return (0);
}

/**
 * _myhelp - prints help message
 * @info: the parameter struct
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    _puts("Help message: Function not yet implemented\n");
    return (0);
}

