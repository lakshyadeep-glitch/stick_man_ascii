
/*
 * Monochrome ASCII Motion - Standalone C Animation
 * No MP4, FFmpeg, Python, or OpenCV required.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>

    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif

    static void sleep_ms(unsigned int ms)
    {
        Sleep(ms);
    }

    static void enable_ansi(void)
    {
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode=0;

        if(h!=INVALID_HANDLE_VALUE && GetConsoleMode(h,&mode))
            SetConsoleMode(h,mode|ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

#else
    #include <time.h>

    static void sleep_ms(unsigned int ms)
    {
        struct timespec t;
        t.tv_sec=ms/1000;
        t.tv_nsec=(long)(ms%1000)*1000000L;
        nanosleep(&t,NULL);
    }

    static void enable_ansi(void) {}
#endif

#define W 80
#define H 30
#define FRAMES 240
#define DELAY_MS 70

static char screen[H][W+1];

static void clear_screen(void)
{
    int y,x;

    for(y=0;y<H;++y)
    {
        for(x=0;x<W;++x)
            screen[y][x]=' ';

        screen[y][W]='\0';
    }
}

static void put_pixel(int x,int y,char c)
{
    if(x>=0 && x<W && y>=0 && y<H)
        screen[y][x]=c;
}

static void disc(int cx,int cy,int radius,char c)
{
    int x,y;

    for(y=-radius;y<=radius;++y)
    {
        for(x=-radius;x<=radius;++x)
        {
            if(x*x+y*y<=radius*radius)
                put_pixel(cx+x,cy+y,c);
        }
    }
}

static void line(int x0,int y0,int x1,int y1,int thickness,char c)
{
    int dx=abs(x1-x0),sx=x0<x1?1:-1;
    int dy=-abs(y1-y0),sy=y0<y1?1:-1;
    int err=dx+dy;

    for(;;)
    {
        disc(x0,y0,thickness,c);

        if(x0==x1 && y0==y1)
            break;

        int e2=2*err;

        if(e2>=dy)
        {
            err+=dy;
            x0+=sx;
        }

        if(e2<=dx)
        {
            err+=dx;
            y0+=sy;
        }
    }
}

static void draw_dancer(int frame)
{
    const double pi=3.14159265358979323846;
    double t=(double)frame*2.0*pi/48.0;

    int cx=40+(int)(3.0*sin(t*0.5));
    int head_x=cx+(int)(2.0*sin(t));
    int head_y=6+(int)(1.0*cos(t*2.0));

    int shoulder_x=cx;
    int shoulder_y=11;

    int hip_x=cx;
    int hip_y=19;

    int left_hand_x=cx+(int)(13.0*cos(t+0.4));
    int left_hand_y=12+(int)(8.0*sin(t+0.4));

    int right_hand_x=cx+(int)(13.0*cos(t+pi-0.4));
    int right_hand_y=12+(int)(8.0*sin(t+pi-0.4));

    int left_foot_x=cx-7+(int)(6.0*sin(t+0.8));
    int left_foot_y=27+(int)(2.0*fabs(sin(t)));

    int right_foot_x=cx+7+(int)(6.0*sin(t+pi+0.8));
    int right_foot_y=27+(int)(2.0*fabs(cos(t)));

    disc(head_x,head_y,3,'#');

    line(shoulder_x,shoulder_y,hip_x,hip_y,2,'#');

    line(shoulder_x,shoulder_y,
         left_hand_x,left_hand_y,1,'#');

    line(shoulder_x,shoulder_y,
         right_hand_x,right_hand_y,1,'#');

    line(hip_x,hip_y,left_foot_x,left_foot_y,2,'#');

    line(hip_x,hip_y,right_foot_x,right_foot_y,2,'#');

    put_pixel(head_x,head_y-1,'@');
    put_pixel(cx,14,'@');
}

static void draw_background(int frame)
{
    int i;

    for(i=0;i<18;++i)
    {
        int x=(i*13+frame*2)%W;
        int y=(i*7+frame/2)%H;

        put_pixel(x,y,'.');
    }

    for(i=0;i<W;i+=4)
        put_pixel(i,H-1,'-');
}

static void render(int frame)
{
    int y;

    clear_screen();
    draw_background(frame);
    draw_dancer(frame);

    printf("\033[H");

    printf("stick man - ORIGINAL ASCII MOTION STUDY\n");
    printf("Frame %3d/%d   Press Ctrl+C to quit\n\n",
           frame+1,FRAMES);

    for(y=0;y<H;++y)
        printf("%s\n",screen[y]);

    fflush(stdout);
}

int main(void)
{
    int frame;

    enable_ansi();

    printf("\033[2J\033[H");

    for(frame=0;frame<FRAMES;++frame)
    {
        render(frame);
        sleep_ms(DELAY_MS);
    }

    printf("\033[2J\033[H");
    printf("Animation complete. Thanks for watching!\n");

    return 0;
}
