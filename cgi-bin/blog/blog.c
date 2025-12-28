#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_header() {
    printf("Content-Type: text/html\r\n\r\n");
}

void print_html_start() {
    printf("<!DOCTYPE html>");
    printf("<html><head>");
    printf("<meta charset='utf-8'>");
    printf("<title>Retro CGI Blog</title>");
    
    printf(" <!-- This blog is using CGI/EXE old skuul method (Handwritten in C) -->");
    printf(" <!-- Author: Matěj Truxa - © 2025 All rights reserved. -->");
    
	printf("<link rel='stylesheet' href='/blog/style.css'>");

    printf("</head><body>");
    printf("<div class='window'>");
    printf("<div class='titlebar'>Retro CGI Blog</div>");
    printf("<div class='content'>");
}

void print_html_end() {
    printf("</div></div>");
    printf("</body></html>");
}

void print_posts() {
    FILE *f = fopen("posts.txt", "r");
    if (!f) {
        printf("<p>Cannot open posts.txt</p>");
        return;
    }

    char line[512];
    char title[256] = "";
    char date[128] = "";
    int in_content = 0;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "===POST===", 10) == 0) {
            printf("<div class='post'>");
        }
        else if (strncmp(line, "TITLE:", 6) == 0) {
            strcpy(title, line + 6);
            printf("<h2>%s</h2>", title);
        }
        else if (strncmp(line, "DATE:", 5) == 0) {
            strcpy(date, line + 5);
            printf("<div class='date'>%s</div>", date);
        }
        else if (strncmp(line, "CONTENT:", 8) == 0) {
            in_content = 1;
            printf("<div class='text'>");
        }
        else if (strncmp(line, "===END===", 9) == 0) {
            in_content = 0;
            printf("</div></div>");
        }
        else if (in_content) {
            printf("%s<br>", line);
        }
    }

    fclose(f);
}

int main() {
    print_header();
    print_html_start();
    print_posts();
    print_html_end();
    return 0;
}
