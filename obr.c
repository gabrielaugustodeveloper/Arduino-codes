#define SETPOINT 50
#define SENSORES_CONST while(sensorE == sensorE_Atual && sensorM == sensorM_Atual && sensorD == sensorD_Atual)

bool sensorE_Atual;
bool sensorM_Atual;
bool sensorD_Atual;

task sensorLuz()
{
    if(Sensor(S1) > SETPOINT)
    {
        sensorE_Atual = 1;
    }
    else
    {
        sensorE_Atual = 0;
    }

    if(Sensor(S2) > SETPOINT)
    {
        sensorM_Atual = 1;
    }
    else
    {
        sensorM_Atual = 0;
    }

    if(Sensor(S3) > SETPOINT)
    {
        sensorD_Atual = 1;
    }
    else
    {
        sensorD_Atual = 0;
    }
}

task sensorUltrassonico()
{
    sensorUs = SensorUS(S4);
}

task main()
{
    SetSensorLight(S1);
    SetSensorLight(S2);
    SetSensorLight(S3);
    SetSensorUltrasonic(S4);

    StartTask(sensorLuz);
    StartTask(sensorUltrassonico);

    while(true)
    {
        until(sensorUs < 5)
        {
            bool sensorE = sensorE_Atual;
            bool sensorM = sensorM_Atual;
            bool sensorD = sensorD_Atual;

            //B = black; W = white
            if(sensorE)
            {
                if(sensorM)
                {
                    if(sensorD) //WWW
                    {
                        SENSORES_CONST
                        {
                            OnFwdSync(OUT_AB, 75); //forward
                        }
                    }
                    else //WWB
                    {
                        SENSORES_CONST
                        {
                            OnFwd(OUT_A, 75); //right
                            OnRev(OUT_B, 75);
                        }
                    }
                }
                else
                {
                    if(sensorD) //WBW
                    {
                        SENSORES_CONST
                        {
                            OnFwdSync(OUT_AB, 75); //forward
                        }
                    }
                    else //WBB
                    {
                        SENSORES_CONST
                        {
                            OnFwd(OUT_A, 75); //right
                            OnRev(OUT_B, 75);
                        }
                    }
                }
            }
            else
            {
                if(sensorM)
                {
                    if(sensorD) //BWW
                    {
                        SENSORES_CONST
                        {
                            OnFwd(OUT_B, 75); //left
                            OnRev(OUT_A, 75);
                        }
                    }
                    else //BWB
                    {
                        //pass
                    }
                }
                else
                {
                    if(sensorD) //BBW
                    {
                        SENSORES_CONST
                        {
                        OnFwd(OUT_B, 75); //left
                        OnRev(OUT_A, 75);
                        }
                    }
                    else //BBB
                    {
                        SENSORES_CONST
                        {
                            OnFwdSync(OUT_AB, 75); //forward
                        }
                    }
                }
            }
        }

        Off(OUT_AB);
        OnRev(OUT_A, 50); //reverse, pointing to right
        OnRev(OUT_B, 75);

        OnFwdSync(OUT_AB, 75); //forward

        until(sensorE < SETPOINT || sensorM < SETPOINT || sensorD < SETPOINT)
        {
            OnFwd(OUT_B, 75); //left
            OnRev(OUT_A, 75);
        }
    }

    //robo resgate
    StopTask(sensorLuz);

    SetSensorType(S1, SENSOR_TYPE_NONE);
    SetSensorType(S2, SENSOR_TYPE_NONE);
    SetSensorType(S3, SENSOR_TYPE_NONE);

    void mover(int angulo, delay, ref)
    {
        RotateMotorEx(OUT_AC, power, angulo, 100, true, true);
        until(sensorUs < 5)
        {
        OnFwdSync(OUT_AB, 75);
        wait(delay);
        switch(ref)
        {
            case 1:
                y++;
                break;
            case 2:
                x++;
                break;
            case 3:
                y--;
                break;
            case 4:
                x--;
                break;
        }
        }
        Off(OUT_AB);
    }

    int posicao[100][2] = {0};
    int x = 0;
    int y = 0;
    int i = 0;

    mover(-180, 0, 0);

    until(encontrar local salvamento)
    {
        x = xAtual;
        y = yAtual;
        i % 4;
        i++;
        mover(180, 500, i);
    }

    RotateMotorEx(OUT_AC, power, 360, 100, true, true);

    until(encontrar vitima)
    {

    }
//1 c, 2 d, 3 b, 4 e 
    void direita()
    {
        x++;
        switch(i)
        {
            case 1:
                RotateMotorEx(OUT_AC, power, 180, 100, true, true);
                break;
            case 3:
                RotateMotorEx(OUT_AC, power, -180, 100, true, true);
                break;
            case 4:
                RotateMotorEx(OUT_AC, power, 360, 100, true, true);
                break;c
        }
    }
    void esquerda()
    {
        x--;
        switch(i)
        {
            case 1:
                RotateMotorEx(OUT_AC, power, -180, 100, true, true);
                break;
            case 2:
                RotateMotorEx(OUT_AC, power, 360, 100, true, true)
                break;
            case 3:
                RotateMotorEx(OUT_AC, power, 180, 100, true, true);
                break;
        }
    }
    void cima()
    {
        y++;
        switch(i)
        {
            case 2:
                RotateMotorEx(OUT_AC, power,-180, 100, true, true)
                break;
            case 3:
                RotateMotorEx(OUT_AC, power, 360, 100, true, true);
                break;
            case 4:
                RotateMotorEx(OUT_AC, power, 180, 100, true, true);
                break;
        }
    }
    void baixo()
    {
        y--;
        switch(i)
        {
            case 1:
                RotateMotorEx(OUT_AC, power, 360, 100, true, true);
                break;
            case 2:
                RotateMotorEx(OUT_AC, power, 180, 100, true, true)
                break;
            case 4:
                RotateMotorEx(OUT_AC, power, -180, 100, true, true);
                break;c
        }
    }
}