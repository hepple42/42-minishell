

# Expander

// Split zu list umwandeln

char	**cmd; 		->string_liste
char	**redirs;	->string_liste
char	**files;	->string_liste

=> dann Wildcards & variables gleichzeitig
=> List to split conversion


=== keine Wildcards in Quotes

heikelste Sache:
"$ARG1"$ARG2

// Split struktur behalten

- Variablen und Wildcards gleichzeitig Ersetzen ???
	- Variablen erfordern nur string manipulation
	- Wildcards erfordern split manipulation


