 #include <stdio.h>
 #include <stdlib.h>
 #include <getopt.h>
 #include <linux/tcp.h>
//#include <gtk/gtk.h>
//#include <glib.h>
#include <unistd.h>
#include <pthread.h>
#include <curl/curl.h>

#define NUMT 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int j = 0;
//gint num_urls = 9; /* Just make sure this is less than urls[]*/
const char * const urls[]= {
  "90022",
  "90023",
  "90024",
  "90025",
  "90026",
  "90027",
  "90028",
  "90029",
  "90030"
};

size_t write_file(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  return fwrite(ptr, size, nmemb, stream);
}

static void run_one(char *http, int j)
{
  FILE *outfile = fopen(urls[j], "wb");
  CURL *curl;

  curl = curl_easy_init();
  if(curl) {
    printf("j = %d\n", j);

    /* Set the URL and transfer type */
    curl_easy_setopt(curl, CURLOPT_URL, http);

    /* Write to the file */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file);
    curl_easy_perform(curl);

    fclose(outfile);
    curl_easy_cleanup(curl);
  }
}

static struct option
long_options[] = {
	{"length", required_argument, 0,  'l' },
	{"help", no_argument,       0,  '?' },
	{"debug", no_argument,       0,  'd' },
	{"trace", required_argument, 0,  't' },
	{"url", no_argument,       0,  'u' },
	{"egress",  required_argument, 0, 'e'},
	{"output",    required_argument, 0,  'o' },
	{"file",    required_argument, 0,  'f' },
	{"ipv6",    required_argument, 0,  '6' },
	{"ipv4",    required_argument, 0,  '4' },
	{0,         0,                 0,  0 }
 };

void usage(char **argv, int argc) {
	printf("%s: Failed\n",argv[0]);
	exit(-1);
}

void parse(char **argv, int argc) {
	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		int c = getopt_long(argc, argv, "abc:d:012",
				long_options, &option_index);
		if (c == -1)
			break;
		switch (c) {
		case 0:
			printf("option                              %s",
			       long_options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
			break;
		case '?':
			break;
		}
		if (optind < argc) {
			printf("non-option ARGV-elements: ");
			while (optind < argc)
				printf("%s ", argv[optind++]);
			printf("\n");
		}
	}
}

		
void main(char **argv, int argc) {
	parse(argv,argc);
}
