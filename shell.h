#ifndef _SHELL_H_
#define _SHELL_H_

// Funkcja wczytujaca komende
char *readLine();
// Funkcja wydobywajaca argumenty z wpisanego wiersza
char **splitLine(char *line);
// Funckja prztwarzajaca argumenty
int launch(char **args, struct HandlerC *headC, struct HandlerR *headR);
// Funkcja główna
void loop(struct HandlerC *headC, struct HandlerR *headR);


 #endif // _SHELL_H_
