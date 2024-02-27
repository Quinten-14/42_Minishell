#include "../../include/minishell.h"

// function to check the type of expansion. Also make it fill in the right
// stuff so for example
// echo $hello$hello gives worldworld if hello=world
// echo $$hello gives [PID]hello
