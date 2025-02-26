#include <Animator.h>
#include <glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
   
    return 0;
}

/*
void gmvConfig(int x, int y, gmvAttrib* att)
{
    if (map[y * c + x].cost == NO_COST) {
        att->num = GMV_NAN;
    }
    else if (map[y * c + x].status == VIS) {
        att->num = map[y * c + x].cost;
        att->color = GMV_RED;
    }
    else if (map[y * c + x].status == EXPD) {
        att->num = map[y * c + x].cost;
        att->color = GMV_YELLOW;
    }

    if (map[y * c + x].from == -1)  att->arrow = GMV_NAARROW;
    else  att->arrow = map[y * c + x].from;

    if (map[y * c + x].status == UNVIS)  att->color = GMV_GREEN;
    else if (map[y * c + x].status == BLOCKED)  att->color = GMV_BLUE;
}

int main(int map_num, char* maps[])
{
    // read the source map of characters from command argument
    FILE* src_map = fopen(maps[1], "r");
    // read the dimension of the map
    if (!fscanf(src_map, "%d%d", &r, &c)) {
        printf("Something wrong with reading the map dimension!\n");
        return -1;
    }
    gmvInit(r, c);
    // create the hash array with bijection y * c + x
    Map m[r * c];
    map = m;
    // read the body of the map
    char tile;
    for (int i = 0; (tile = fgetc(src_map)) != EOF;) {
        if (tile == '\n')  continue;
        if (tile != '.')  map[i].status = BLOCKED;
        else  map[i].status = UNVIS;
        map[i].from = tile;
        map[i++].cost = NO_COST;
    }
    // reading the source and target state and run the algorithm
    int sx, sy, tx, ty;
    if (!scanf("%d%d%d%d", &sx, &sy, &tx, &ty))  return -1;
    #ifndef ALG
    printf("ALG is not defined!\n");
    return -1;
    #endif//ALG
    printf("%d\n", ALG(sy * c + sx, ty * c + tx));
    
    return 0;
}
*/