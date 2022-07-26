#include <unistd.h>
#include <stdio.h>

int main (void) 
{
    int	result;

    result = access ("file", F_OK);
    if (result == 0)
    {
        unlink("file");
        printf("Deleted\n");
    }    
    else
        printf("Error\n");
    return (0);
}


forfiles /p C: \Windows\System32\winevt\Logs /D -1 > C\Users\User\Desktop\Prueba\Prueba.txt