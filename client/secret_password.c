#include "head.h"
#include "secret_password.h"

int getch()
{
	int c=0;
	struct termios org_opts, new_opts;
	int res=0;
	//-----  store old settings -----------
	res=tcgetattr(STDIN_FILENO, &org_opts);
	assert(res==0);
	//---- set new terminal parms --------
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c=getchar();
	//------  restore old settings ---------
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res==0);
	return c;
}

char *Secret_Password()
{
	int i = 0;
	char *pd = (char *)malloc(64);

	while (1)
	{
		pd[i] = getch();

		if ('\n' == pd[i])
		{
			pd[i] = '\0';
			break;
		}
		if (127 == pd[i])
		{
			if (0 == i)
			{
				continue;
			}
			printf("\b \b");
			i = i - 1;
			continue;
		}
		else
		{
			printf("*");
		}
		i++;
	}
	return pd;
}
