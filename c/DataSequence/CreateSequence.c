//====================================================================
//  工学部「情報環境実験１」  例題プログラム
//  指定範囲の乱数と乱列の生成
//--------------------------------------------------------------------
//  ObjSort CreateSequence.c
//  Linux  GCC 4.4
//--------------------------------------------------------------------
//  富永研究室  tominaga 富永浩之
//  2017.06.22
//====================================================================


//====================================================================
//  概略仕様
//====================================================================


//====================================================================
//  事前処理
//====================================================================

#include <stdio.h>
#include <stdlib.h>

#include "../RandomData/RandomData.h"
#include "../DataSequence/DataSequence.h"


//====================================================================
//  データ列の生成
//====================================================================

//--------------------------------------------------------------------
//  整列済のデータ列
//--------------------------------------------------------------------

void CreateSequence_normal(DataSequence *seq) 
{
    //----  局所宣言
    int pos;

    //----  データ列の生成
    for ( pos = 0; pos < seq->size; pos++ ) {  
        seq->arr[pos] = pos;                     // 添字を格納
    }
}

//--------------------------------------------------------------------
//  乱数化のデータ列
//--------------------------------------------------------------------

void CreateSequence_random(DataSequence *seq) 
{
    //----  局所宣言

    int pos;

    //----  データ列の生成

    for ( pos = 0; pos < seq->size; pos++ ) {  
        seq->arr[pos] = irand(seq->size);         // num未満の整乱数を格納
    }
}

//--------------------------------------------------------------------
//  端末入力のデータ列
//--------------------------------------------------------------------

void CreateSequence_input(DataSequence *seq) 
{
    //----  局所宣言
    int pos;
    int data;

    //----  端末入力の事前処理
    printf("?  ");

    //----  データ列の生成
    for ( pos = 0; pos < seq->size; pos++ ) {  
        scanf("%d", &data);     // 端末からの入力
        seq->arr[pos] = data;    // データの格納
    }
}

//--------------------------------------------------------------------
//  ファイル読出のデータ列
//--------------------------------------------------------------------

void CreateSequence_file(DataSequence *seq, String fname) 
{
    //----  局所宣言
    int pos;
    int data;
    FILE *fp;

    //----  ファイルの事前処理
    if ( (fp = fopen(fname, "r")) == NULL ) { 
        fprintf(stderr, "Failure\n");
        exit(EXIT_FAILURE);
    }

    //----  データ列の生成
     for ( pos = 0; pos < seq->size; pos++ ) {  
        fscanf(fp, "%d", &data);    // ファイルからの入力
        seq->arr[pos] = data;        // データの格納
    }

    //----  ファイルの事後処理
    fclose(fp);
}

//--------------------------------------------------------------------
//  回数指定による撹拌のデータ列
//--------------------------------------------------------------------

void CreateSequence_exchange(DataSequence *seq, int exc) 
{
    //----  局所宣言
    int pos1;
    int pos2;

    //----  データ列の生成
    CreateSequence_normal(seq);                 // 整列データ列の生成

    //----  データ列の撹拌
    while ( exc > 0 ) {                         // exc回だけ交換
        pos1 = irand(seq->size); 
        pos2 = irand(seq->size); 
        // if ( pos1 == pos2 ) { continue; }    // 強制交換のとき
        DataSequence_swap(seq, pos1, pos2);     // 要素の交換
        exc--;
    }
}

//--------------------------------------------------------------------
//  確率指定による撹拌のデータ列
//--------------------------------------------------------------------

void CreateSequence_shuffle(DataSequence *seq, double prb) 
{
    //----  局所宣言
    int pos1;
    int pos2;

    //----  データ列の生成
    CreateSequence_normal(seq);                     // 整列データ列の生成

    //----  データ列の撹拌
    for ( pos1 = 1; pos1 < seq->size; pos1++ ) {    
        if ( frand() >= prb ) { continue; }         // 確率prb未満のときのみ
        pos2 = irand(pos1+1);                       // pos1以下の整乱数
        DataSequence_swap(seq, pos1, pos2);         // 要素の交換
    }
}
