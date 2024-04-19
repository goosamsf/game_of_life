Cal Poly CPE419 : Game of Life

Instruction : After compilation process(make), run executable.
              ./game (running without argument)  : running in serial
              ./game p(running with argument) : running in parallel

Number of thread : 1

| matrix size | Elapsed |
|-----------  | ------- |
| 20 x 20     |  0.005  |
|-----------  | ------- |
| 100 x 100   |  0.03   |
|-----------  | ------- |
|1000 x 1000  |  1.73   |
|----------   | ------- 


Number of thread : 2 

| matrix size | Elapsed |
|-----------  | ------- |
| 20 x 20     |  0.003  |
|-----------  | ------- |
| 100 x 100   |  0.02   |
|-----------  | ------- |
|1000 x 1000  |   0.9   |
|----------   | ------- 


Number of thread : 4 

| matrix size | Elapsed |
|-----------  | ------- |
| 20 x 20     |  0.01   |
|-----------  | ------- |
| 100 x 100   |  0.02   |
|-----------  | ------- |
|1000 x 1000  |  0.5   |
|----------   | ------- 


Number of thread : 8

| matrix size | Elapsed |
|-----------  | ------- |
| 20 x 20     |  0.003  |
|-----------  | ------- |
| 100 x 100   |  0.01   |
|-----------  | ------- |
|1000 x 1000  |   0.27  |
|----------   | ------- 

Number of thread : 16

| matrix size | Elapsed |
|-----------  | ------- |
| 20 x 20     |  0.003  |
|-----------  | ------- |
| 100 x 100   |  0.01   |
|-----------  | ------- |
|1000 x 1000  |  0.25   |
|----------   | ------- 
