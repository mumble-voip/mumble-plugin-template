#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pwd.h>
#endif

#define POSITION_INFO_PATH "/Factorio/script-output/player_position.txt"

/**
 * @brief Get the string for the home directory
 * This is OS dependent
 *
 * @return char* home directory string
 */
char *get_home_dir()
{
#ifdef _WIN32
    char *appdata = getenv("APPDATA");
    return appdata;
#else
    char *homeDir = getenv("HOME");
    if (!homeDir)
    {
        struct passwd *pwd = getpwuid(getuid());
        if (pwd)
            homeDir = pwd->pw_dir;
    }
    return homeDir;
#endif
}

/**
 * @brief Check if file exists
 *
 * @param fname filename
 * @return int 1 if it exists, 0 if it does not
 */
int file_exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

/**
 * @brief Check if the factorio logfile is present
 *
 * @return int 1 if it exists, 0 if it does not
 */
int is_factorio_logfile_there()
{
    char *homeDir = get_home_dir();
    char *factorioLogfile = malloc(strlen(homeDir) + strlen(POSITION_INFO_PATH) + 1);
    strcpy(factorioLogfile, homeDir);
    strcat(factorioLogfile, POSITION_INFO_PATH);
    return file_exists(factorioLogfile);
}

/**
 * @brief Loads Factorio log file and assigns values to given pointers
 *
 * @param x x coordinate
 * @param y y coordinate
 * @param z z coordinate
 * @param player player id (integer)
 * @param surface surface id (integer)
 * @param server server id (string) - username of host
 * @param server_len length of server string
 */
void parse_factorio_logfile(float *x, float *y, float *z, int *player, int *surface, char **server, size_t *server_len)
{
    char *homeDir = get_home_dir();
    char *factorioLogfile = malloc(strlen(homeDir) + strlen(POSITION_INFO_PATH) + 1);
    strcpy(factorioLogfile, homeDir);
    strcat(factorioLogfile, POSITION_INFO_PATH);

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(factorioLogfile, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // skip first line
        if (strstr(line, "XYZ") != NULL)
        {
            continue;
        }
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);

        char *token = strtok(line, ":");
        char *value = strtok(NULL, ":");

        // printf("token: %s\n", token);
        // printf("value: %s\n", value);

        if (strcmp(token, "x") == 0)
        {
            *x = atof(value);
        }
        else if (strcmp(token, "y") == 0)
        {
            *y = atof(value);
        }
        else if (strcmp(token, "z") == 0)
        {
            *z = atof(value);
        }
        else if (strcmp(token, "p") == 0)
        {
            *player = atoi(value);
        }
        else if (strcmp(token, "u") == 0)
        {
            *surface = atoi(value);
        }
        else if (strcmp(token, "s") == 0)
        {
            // strip newline if present
            if (value[strlen(value) - 1] == '\n')
            {
                value[strlen(value) - 1] = '\0';
            }
            *server_len = strlen(value);
            *server = malloc(*server_len + 1);
            strcpy(*server, value);
        }
    }

    fclose(fp);
    if (line)
        free(line);
}

int main(int argc, char **argv)
{
    char *homeDir = get_home_dir();
    printf("Home dir: %s\n\n", homeDir);

    if (is_factorio_logfile_there())
    {
        printf("Factorio logfile is present\n\n");
    }
    else
    {
        printf("Factorio logfile is not present. Terminating...\n");
        return 0;
    }

    float x, y, z;
    int player, surface;
    char *server;
    size_t server_len;

    parse_factorio_logfile(&x, &y, &z, &player, &surface, &server, &server_len);

    // log variables
    printf("x: %f\n", x);
    printf("y: %f\n", y);
    printf("z: %f\n", z);
    printf("player: %d\n", player);
    printf("surface: %d\n", surface);
    printf("server: %s\n", server);

    // combine surface and server
    char *context_str = malloc(server_len + 1 + 1 + 1);
    strcpy(context_str, server);
    strcat(context_str, "/");
    char surface_str[12];
    sprintf(surface_str, "%d", surface);
    strcat(context_str, surface_str);
    char *context = context_str;

    printf("context: %s\n", context_str);

    return 0;
}
