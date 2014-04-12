#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#ifndef WIN32
# include <unistd.h>
#else
# include <process.h>
# define snprintf sprintf_s
#endif

#include <mosquitto.h>

#define mqtt_host "192.168.1.72"
#define mqtt_port 1883

//ale mele

#define PI 3.1415
#define ypsus 270
#define ypjos 450
#define portar 11
#define idportar "in11"
#define minge 0
#define idminge "in0"
#define fundas 9
#define idfundas "in9"
#define atacant 8
#define idatacant "in8"
#define xpoarta 880
#define timpmiscareportar 0
#define offset 25
#define yminim  80
#define ymax   680


struct control
{
    int left;
    int right;
    int time;
} ctr[20];

struct robotCoords
{
    int id;/*id robot - 1..10*/
    int x; /*// 0...800 - relative la terenul de joc*/
    int y; /*// 0...600*/
    int angle; /*// unghi fata de baza ringului*/
    int timestamp; /*// timpul cand au fost calculate - UNIXTIME - Ex: 1352460922*/
} coordrob[20];

struct timeval tv;
static int run = 1;
struct mosquitto *mosq;
int mid;

void handle_signal(int s)
{
    run = 0;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    struct robotCoords *coordonate = (struct robotCoords *)message->payload;
    if (coordonate->id == 0)
    {
        if (coordonate->x != 0 && coordonate->y != 0)
        {
            coordrob[coordonate->id].angle = coordonate->angle;
            coordrob[coordonate->id].timestamp = coordonate->timestamp;
            coordrob[coordonate->id].x = coordonate->x;
            coordrob[coordonate->id].y = coordonate->y;
        }
    }
    else
    {
        coordrob[coordonate->id].angle = coordonate->angle;
        coordrob[coordonate->id].timestamp = coordonate->timestamp;
        coordrob[coordonate->id].x = coordonate->x;
        coordrob[coordonate->id].y = coordonate->y;
    }

}
void progportar ()
{
    if (coordrob[minge].x < 430) //se schimba daca jucam in partea dreapta
    {
        if (coordrob[portar].x < xpoarta - 15)
        {
            if (coordrob[portar].angle < 270 && coordrob[portar].angle > 90)
            {
                ctr[portar].right = -70;
                ctr[portar].left = -70;
                ctr[portar].time = timpmiscareportar;
            }
            else
            {
                ctr[portar].right = 70;
                ctr[portar].left = 70;
                ctr[portar].time = timpmiscareportar;
            }
        }
        else if (ypsus - coordrob[portar].y > 15)
        {
            ctr[portar].left = -40;
            ctr[portar].right = -40;
            ctr[portar].time = timpmiscareportar;
        }
        else if (coordrob[portar].y - ypjos > 15)
        {
            ctr[portar].left = -40;
            ctr[portar].right = -40;
            ctr[portar].time = timpmiscareportar;
        }
        else if (coordrob[portar].angle > 285)
        {
            ctr[portar].right= -40;
            ctr[portar].left= 40;
            ctr[portar].time=30;
        }
        else if (coordrob[portar].angle < 255)
        {
            ctr[portar].right= 40;
            ctr[portar].left= -40;
            ctr[portar].time = 30;
        }
    }
    else
    {
        if ((abs(coordrob[portar].y - ypsus)< 15) && (coordrob[minge].y < coordrob[portar].y))
        {
            ctr[portar].right = 0;
            ctr[portar].left = 0;
            ctr[portar].time = timpmiscareportar;
        }
        else if((coordrob[portar].y - ypsus > 15) && (coordrob[minge].y < coordrob[portar].y))
        {
            ctr[portar].right = -50;
            ctr[portar].left = -50;
            ctr[portar].time = timpmiscareportar;
        }
        if ((abs(coordrob[portar].y - ypjos) < 15) && (coordrob[minge].y > coordrob[portar].y))
        {
            ctr[portar].right = 0;
            ctr[portar].left = 0;
            ctr[portar].time = timpmiscareportar;
        }
        else if ((coordrob[portar].y - ypjos < -15) && (coordrob[minge].y > coordrob[portar].y))
        {
            ctr[portar].right = 50;
            ctr[portar].left = 50;
            ctr[portar].time = timpmiscareportar;
        }

        if ((coordrob[minge].y < ypjos) && (coordrob[minge].y > ypsus))
            if (coordrob[portar].y > coordrob[minge].y)
            {
                ctr[portar].right = -40;
                ctr[portar].left = -40;
                ctr[portar].time = timpmiscareportar;
            }
        if (coordrob[portar].y < coordrob[minge].y)
        {
            ctr[portar].right = 40;
            ctr[portar].left = 40;
            ctr[portar].time = timpmiscareportar;
        }

        if (ypsus - coordrob[portar].y >15)
        {
            ctr[portar].left = 40;
            ctr[portar].right = 40;
            ctr[portar].time = timpmiscareportar;
        }
        if (coordrob[portar].y - ypjos > 15)
        {
            ctr[portar].left = -40;
            ctr[portar].right = -40;
            ctr[portar].time = timpmiscareportar;
        }
    }
}



int unghiuldorit(int id,int x,int y)
{
    double m;
    m = atan2((double)(coordrob[id].y- y), (double)(coordrob[id].x - x));
    m = m * 180 / PI;
    if (m < 0) m = m + 360;
    m = 360 - m;
    //  printf ("\n\n\n panta: %lf unghi: %d\n \n \n" , m, coordrob[atacant].angle);
    return m;

}

int unghiuldorit2(int id,int x,int y)
{
    double m;

    if ((coordrob[id].x - offset - x) > 0)
    {
        m = atan2((double)(coordrob[id].y - y - 10), (double)(coordrob[id].x - offset - x));
        m = m * 180 / PI;
        if (m < 0) m = m + 360;
        m = 360 - m;
        printf ("\n\n\n panta: %lf        unghi: %d\n \n \n" , m, coordrob[atacant].angle);
        return m;
    }
    else
    {
        m = atan2((double)(coordrob[id].y- y), (double)(coordrob[id].x - x));
        m = m * 180 / PI;
        if (m < 0) m = m + 360;
        m = 360 - m;
        printf ("\n\n\n panta: %lf        unghi: %d\n \n \n" , m, coordrob[atacant].angle);
        return m;
    }

}

int travel (char* idid, int id, int x, int y)
{
    int c= x - coordrob[id].x;
    int b= y - coordrob[id].y;
    float distance = b*b + c*c;

    if (distance < 200)
    {
        ctr[id].right = 0;
        ctr[id].left = 0;
    }
    else
    {
        ctr[id].right = 150;
        ctr[id].left = 150;
        ctr[id].time = 0;

    }
    return distance;
}

void calculate_robot_next_movement()
{
    struct robotCoords thisR = coordrob[atacant];
    double m = unghiuldorit(minge, coordrob[atacant].x,coordrob[atacant].y);
    double m2 = unghiuldorit(minge, coordrob[fundas].x,coordrob[fundas].y);
    double m3 = unghiuldorit2(minge, coordrob[fundas].x,coordrob[fundas].y);
    double m4 = unghiuldorit2(minge, coordrob[atacant].x,coordrob[atacant].y);
    if (coordrob[atacant].x <= coordrob[minge].x)
    {
        if((coordrob[atacant].angle> (m4 - 25)) && (coordrob[atacant].angle < (m4 + 25)))
        {
            travel(idatacant,atacant,coordrob[minge].x + offset,coordrob[minge].y + offset);
        }
        else
        {
            if (coordrob[atacant].angle - m4< 0)
            {
                ctr[atacant].left = 90;
                ctr[atacant].right = -30;
                ctr[atacant].time = 45;
            }
            else
            {
                ctr[atacant].left = -30;
                ctr[atacant].right = 90;
                ctr[atacant].time = 45;
            }
        }

    }
    else if((thisR.angle> (m - 25)) && (thisR.angle < (m + 25)))
    {
        travel(idatacant,atacant,coordrob[minge].x,coordrob[minge].y);
    }
    else
    {
        ctr[atacant].left = 90;
        ctr[atacant].right = -30;
        ctr[atacant].time = 45;
    }


    if (coordrob[fundas].x <= coordrob[minge].x)
    {
        if((coordrob[fundas].angle> (m3 - 25)) && (coordrob[fundas].angle < (m3 + 25)))
        {
            travel(idfundas,fundas,coordrob[minge].x + offset,coordrob[minge].y + offset);
        }
        else
        {
            if (coordrob[fundas].angle - m3< 0)
            {
                ctr[fundas].left = 90;
                ctr[fundas].right = -30;
                ctr[fundas].time = 45;
            }
            else
            {
                ctr[fundas].left = -30;
                ctr[fundas].right = 90;
                ctr[fundas].time = 45;
            }
        }

    }
    else if((coordrob[fundas].angle> (m2 - 25)) && (coordrob[fundas].angle < (m2 + 25)))
    {
        travel(idfundas,fundas,coordrob[minge].x,coordrob[minge].y);
    }
    else
    {
        ctr[fundas].left = 90;
        ctr[fundas].right = -30;
        ctr[fundas].time = 45;
    }

    if (coordrob[atacant].y < yminim)                               //asta nu se schimba daca schimbat portile
    {
        if (coordrob[atacant].angle > 180 && coordrob[atacant].angle < 360)
        {
            ctr[atacant].left = 100;
            ctr[atacant].right = 80;
            ctr[atacant].time = 0;
        }
        else
        {
            if (coordrob[atacant].angle < 180)
            {
                ctr[atacant].left = -100;
                ctr[atacant].right = -80;
                ctr[atacant].time = 0;
            }
        }
    }
    if (coordrob[atacant].y > ymax)                                                 //asta nu se schimba daca schimbat portile
    {
        if (coordrob[atacant].angle > 180 && coordrob[atacant].angle < 360)
        {
            ctr[atacant].left = -100;
            ctr[atacant].right = -80;
            ctr[atacant].time = 0;
        }
        else
        {
            if (coordrob[atacant].angle < 180)
            {
                ctr[atacant].left = 80;
                ctr[atacant].right = 100;
                ctr[atacant].time = 0;
            }
        }
    }


    if (coordrob[fundas].y < yminim)                   //asta nu se schimba daca schimbat portile
    {
        if (coordrob[fundas].angle > 180 && coordrob[fundas].angle < 360)
        {
            ctr[fundas].left = 100;
            ctr[fundas].right = 80;
            ctr[fundas].time = 0;
        }
        else
        {
            if (coordrob[fundas].angle < 180)
            {
                ctr[fundas].left = -100;
                ctr[fundas].right = -80;
                ctr[fundas].time = 0;
            }
        }
    }
    if (coordrob[fundas].y > ymax)                          //asta nu se schimba daca schimbat portile
    {
        if (coordrob[fundas].angle > 180 && coordrob[fundas].angle < 360)
        {
            ctr[fundas].left = -100;
            ctr[fundas].right = -80;
            ctr[fundas].time = 0;
        }
        else
        {
            if (coordrob[fundas].angle < 180)
            {
                ctr[fundas].left = 80;
                ctr[fundas].right = 100;
                ctr[fundas].time = 0;
            }
        }
    }



    progportar();
}

void do_robot_control_loop()
{
    int mid;

    fflush(stdout);

    calculate_robot_next_movement();
    printf ("salut  coord y: %d      coord X: %d\n\n\n", coordrob[portar].y,coordrob[portar].x);
    mosquitto_publish(mosq, &mid, idatacant, sizeof(struct control), &ctr[atacant], 0, false);
    mosquitto_publish(mosq, &mid, idportar, sizeof(struct control), &ctr[portar], 0, false);
    mosquitto_publish(mosq, &mid, idfundas, sizeof(struct control), &ctr[fundas], 0, false);

    //mosquitto_loop(mosq, 1, 50);
    gettimeofday(&tv, NULL);
}

int need_to_send()
{
    struct timeval now;

    gettimeofday(&now, NULL);

    if(tv.tv_usec > 800000)
        gettimeofday(&tv, NULL);

    if(now.tv_usec >= tv.tv_usec + 100000)
    {
        return 1;
    }

    return 0;
}
int main(int argc, char *argv[])
{
    char clientid[24]="FcBitu'";
    int rc = 0;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, true, NULL);
    if(mosq)
    {
        mosquitto_connect_callback_set(mosq, connect_callback);
        mosquitto_message_callback_set(mosq, message_callback);
        rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);
        mosquitto_subscribe(mosq, NULL, "coords", 0);
        mosquitto_loop_start(mosq);
        gettimeofday(&tv,NULL);

        while(run)
        {
            if(run && rc)
            {
                sleep(2);
                printf ("\n run: %d rc: %d \n", run,rc);
                mosquitto_reconnect(mosq);
            }
            // incepe softul propriuzis
            calculate_robot_next_movement();

            if(need_to_send())
            {
                do_robot_control_loop();
            }
            fflush(stdout);
        }
        mosquitto_destroy(mosq);
    }

    mosquitto_lib_cleanup();

    return rc;
}
