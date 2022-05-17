#include "shell.h"

int main(int argc __attribute__ ((unused)), char **argv)
{
	char *strinput = NULL, *token = NULL, **storetoken = NULL;
	char *cmdinpath = NULL, *delim = "\n ",  prompt[] = "($) ";
	int readnum, i = 0, errnum = 0, size = 0, counter = 0, CDvalue = 0;
	int  cerrnum = 0;
	size_t len = 0;
	pid_t childpid;
	PDIRECT *head = NULL;
	CHDIRECT predirect;

	predirect.s = _strdup(_getenv("HOME"));
	head = linkedpath();
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		storetoken = NULL;

		predirect.boo = 0;
		counter++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 4);
		i = 0;
		readnum = getline(&strinput, &len, stdin);
		if (readnum == -1)
		{
			__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);
		}
		size = tokencount(strinput) + 1;

		if (size == 1)
			continue;
		token = _strtok(strinput, delim);

		storetoken = malloc(sizeof(char *) * size);
		storetoken[i++] = token;
		while (token != NULL)
		{
			token = _strtok(NULL, delim);
			storetoken[i++] = token;
		}
		i = 0;

		
		CDvalue = changedir(storetoken, &predirect);
		if (CDvalue  == -1) 
			CDerrmessage(storetoken, argv[0], counter);

		childpid = fork();

		if (childpid == -1)
			__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);

		if (childpid == 0)
		{

			if (checkenv(storetoken)) 
				__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);
			cerrnum = checkexit(storetoken);
			if (cerrnum != -1)
				__exit(cerrnum, storetoken, strinput, head, cmdinpath, predirect.s);

			execve(storetoken[0], storetoken, environ);
			cmdinpath = findcommand(head, storetoken[0]);
			execve(cmdinpath, storetoken, environ);
			if (!predirect.boo)
				errmessage(storetoken, argv[0], counter);
			errnum = 0;
			__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);
		}
		else
		{
			wait(NULL);
			cerrnum = checkexit(storetoken);
			if (cerrnum != -1)
				__exit(cerrnum, storetoken, strinput, head, cmdinpath, predirect.s);

		}
		if (storetoken)
			free(storetoken);
	}
	return (0);
}

