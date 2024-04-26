    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <GL/glut.h>
    // #include <bits/stdc++.h>
    #define ll long long
    #define ld long double
    #define pb push_back
    #define ff first    
    #define ss second 
    #define all(x) x.begin(), x.end()
    #define lb lower_bound
    #define ub upper_bound
    #define ins insert
    #define vi vector<ll> 
    #define sz size()  
    #define ic(xra) ll xra;   cin >> xra;
    #define sc(xra) string xra;  cin >> xra;
    #define floi(xra, xrn, xrc) for (ll i = xra; i < xrn; i += xrc)
    #define floj(xra, xrn, xrc) for (ll j = xra; j < xrn; j += xrc)
    #define flori(xra, xrn, xrc) for (ll i = xra; i >= xrn; i -= xrc)    
    #define florj(xra, xrn, xrc) for (ll j = xra; j >= xrn; j -= xrc)
    #define vin(xrn, xrv) vi xrv; for (ll i = 0; i < xrn; i++)  {  ll xra;  cin >> xra;  xrv.pb(xra); }
    #define gcd(a, b) __gcd(a, b)
    #define lcm(a, b) a *b / gcd(a, b)
    #define INF 1e18

#define MAX 100    // Number of values in the array
#define COLORS 100 // Max Color Length

/*~~Global Variables~~*/
int a[MAX];        // Sorting Array
double cc[COLORS]; // Color Array
int swapflag = 0; // Flag to check if swapping has occurred
int i = 0, j = 0; // To iterate through the array
int flag = 0;     // For Insertion Sort
int dirflag = 0;  // For Ripple Sort, to change direction at the ends
int count = 1;    // For Ripple Sort, to keep count of how many are sorted at the end
int sorting = 0;  // 1 if Sorted
const char *sort_string[] = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Comb Sort"};
int sort_count = 0; // To cycle through the string
int speed = 1;     // Speed of sorting
int arrayFlag = 1;
int backFlag = 1;
int fastslow = 0;
int vertical_index;

/*{~~Function Declarations~~*/
double randomFloat();
void bitmap_output(int, int, const char *, void *);
void display_text();
void Initialize();
void display();
void int_str(int rad, char r[]);
int notsorted();
void keyboard(unsigned char key, int x, int y);
void ripplesort();
void bubblesort();
void selectionsort();
void insertionsort();
void combSort();

/*~~Function Definitions~~*/

// Function to get random number between 0.0 to 1.0
double randomFloat() {
    return (double)rand() / (double)RAND_MAX;
}

// Function to display text on screen char by char
void bitmap_output(int x, int y, const char *string, void *font) {
    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 'k')
    {
        speed = 1;
    }
    else if (sorting != 1)
    {
        switch (key)
        {
        case 27:
            exit(0); // 27 is the ascii code for the ESC key
        case 's':
            sorting = 1;
            break;
        case 'i':
            fastslow = 1;
            break;
        case 'o':
            fastslow = 0;
            break;
        case 'r':
            arrayFlag = 1;
            Initialize();
            break;
        case 'x':
            backFlag = 1;
            arrayFlag = 0;
            Initialize();
            break;
        case 'z':
            arrayFlag = 1;
            backFlag = 1;
            Initialize();
            break;
        case 'c':
            sort_count = (sort_count + 1) % SORT_NO;
            break;
        }
    }
    else
    {
        if (key == 'p')
            sorting = 0;
        speed = 1000;
    }
}


// Function to integer to string
void int_str(int rad, char r[]) {
    snprintf(r, 10, "%d", rad);
}


// Initialization of values also called whenever 'r' key is pressed
void Initialize()
{
    srand(time(0)); // Use current time as seed for random generator

    if (arrayFlag == 1)
    {
        // Reset the array
        for (int temp1 = 0; temp1 < MAX; temp1++)
        {
            a[temp1] = rand() % 100 + 1;
        }
        arrayFlag = 0;
    }

    if (backFlag == 1)
    {
        for (int i = 0; i < COLORS; i++)
        {
            cc[i] = randomFlaot();
        }

        // Reset all values
        i = j = 0;
        dirflag = 0;
        count = 1;
        flag = 0;
        glClearColor(randomFlaot(), randomFlaot(), randomFlaot(), randomFlaot());
        backFlag = 0;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 699, 0, 799);
}

// Check elements before calling sorting functions
int notsorted() {
    int q;
    for (q = 0; q < MAX - 1; q++) {
        if (a[q] > a[q + 1])
            return 1; // Return 1 if not sorted
    }
    return 0;
}

// Main function for display
void display()
{
    int ix, temp;
    glClear(GL_COLOR_BUFFER_BIT);
    display_text();
    char text[10];
    if (swapflag == 1 || sorting == 0)
    {
        glBegin(GL_POLYGON);
        glColor3d(cc[75], cc[76], cc[77]);
        glColor3d(cc[78], cc[79], cc[80]);
        glVertex2f(10 + (700 / (MAX + 1)) * vertical_index, 50);
        glColor3d(cc[81], cc[82], cc[83]) ;
        glEnd();
        swapflag = 0;
    }
    glFlush();
}


// Insertion Sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
// A utility function to print
// an array of size n
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Selection Sort

void selectionsort()
{
    int temp, j, min, pos;

    while (notsorted())
    {

        while (i < MAX - 1)
        {
            min = a[i + 1];
            pos = i + 1;
            if (i != MAX - 1)
            {
                for (j = i + 2; j < MAX; j++)
                {
                    if (min > a[j])
                    {
                        min = a[j];
                        vertical_index = i;
                        pos = j;
                    }
                }
            }
            printf("\ni=%d min=%d at %d", i, min, pos);
            printf("\nchecking %d and %d", min, a[i]);
            if (min < a[i])
            {

                //j=pos;
                int_str(min, text1);
                int_str(a[i], text2);
                printf("\nswapping %d and %d", min, a[i]);
                temp = a[pos];
                a[pos] = a[i];
                a[i] = temp;
                // vertical_index = min;
                swapflag = 1; //change
                goto A;
            }
            i++;
        }
    }
    sorting = 0;
    i = j = 0;
A:
    printf(" ");
}


// Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}



void combSort(int a[], int n)
{
    // Initialize gap
    int gap = n;
 
    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;
 
    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true)
    {
        // Find next gap
        gap = getNextGap(gap);
 
        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;
 
        // Compare all elements with current gap
        for (int i=0; i<n-gap; i++)
        {
            if (a[i] > a[i+gap])
            {
                swap(a[i], a[i+gap]);
                swapped = true;
            }
        }
    }
}
// Main Function
int main(int argc, char **argv) {
    // Main function...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(2000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CG lab project ");
    Initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, makedelay, 100);
    glutMainLoop();

}
