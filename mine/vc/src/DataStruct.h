//DataStruct.h
#pragma once

#define conIsMine       1   //是地雷
#define conDiscovered   2   //被打开
#define conMarked       4   //被标上?号
#define conFounded      8   //被发现(插上红旗)
#define conChoosed      16  //被选中

#define STA_NONE        0   //还没有开始挖雷
#define STA_WORKING     1   //正在挖雷
#define STA_OK          2   //已经挖好
#define STA_DIED        3   //死亡

#define FACE_DOWN       0   //下陷脸型
#define FACE_OK         1   //胜利脸型
#define FACE_DIED       2   //死亡脸型
#define FACE_WORK       3   //工作脸型
#define FACE_WAIT       4   //等待脸型

typedef struct tagBlock
{
    BYTE Totalmines;
    BYTE Flag;
}BLOCK;

typedef struct tagIniInfo
{
    int     Difficulty;
    int     Height;
    int     Width;
    int     Mines;
    int     Mark;    
    int     Xpos;
    int     Ypos;
    int     Time1;
    int     Time2;
    int     Time3;
    CString Name1;
    CString Name2;
    CString Name3;
    int     Protect;
    //Color =1
}INIINFO;
