#include "tetris.h"

static struct sigaction act, oact;

typedef struct _NODE{
	char name[NAMELEN];
	int score;
	struct _NODE *link;
}NODE;

NODE *head=NULL;

RecNode *root;
RecNode *answernode; 

int R_y,R_x,R_ID,R_rotate;


int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	
	createRankList();
	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;
	root = malloc(sizeof(RecNode));
	root->lv=0;
	tree(root);
	recommend(root);

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
	move(9,WIDTH+10);
	DrawBox(9,WIDTH+10,4,8);
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(15,WIDTH+10);
	printw("SCORE");
	DrawBox(16,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(17,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for( i = 0; i < 4; i++ ){
	move(10+i,WIDTH+13);
	for( j = 0; j < 4; j++ ){
		if( block[nextBlock[2]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
		        else printw(" ");
		}
	}

}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
		int t_i =0, t_j =0;
			int i,j;
				for(i=0; i<4; i++) {
		for(j=0; j<4; j++){
				if(block[currentBlock][blockRotate][i][j] == 1){
					t_i = blockY + i; t_j = blockX + j;
			if(!(0<=t_j && t_j<WIDTH && 0<=t_i && t_i < HEIGHT)) // 벗어남
			return 0;
				if(f[t_i][t_j]==1) // 이미 블록 있음
		return 0;
}
}
}
return 1;
// user code
}
void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int i,j;
	int x = blockX, y = blockY, c=blockRotate;
	int sha_y=y;
	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	switch(command) {
		case KEY_UP:
			c = (c+3)%4; 	
			break;
		case KEY_DOWN:
			y--;
			break;
		case KEY_LEFT:
			x++;
			break;
		case KEY_RIGHT:
			x--;
			break;
	}
	while(CheckToMove(field,currentBlock,c,sha_y,x))
		sha_y++;
	sha_y--;

	

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (block[currentBlock][c][i][j] == 1 && i + sha_y >= 0)
			{
				move(i+sha_y+1,j+x+1);
				printw(".");
			}
			if (block[currentBlock][c][i][j] == 1 && i + y >= 0) {
				move(i + y + 1, j + x + 1);
				printw(".");
				}
			}
		}
	recommend(root);
	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);//3. 새로운 블록 정보를 그린다. 
	 move(HEIGHT,WIDTH+10);

}

void BlockDown(int sig){
	// user code
	if (CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX) == 1) {
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else {
		score += AddBlockToField(field,nextBlock[0],blockRotate,blockY,blockX);
		if (blockY == -1) 
			gameOver = 1;
		
		AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		score += DeleteLine(field);
		nextBlock[0]=nextBlock[1];
		nextBlock[1]=nextBlock[2];
		nextBlock[2]=rand()%7;
		DrawNextBlock(nextBlock);
		
		blockY = -1;
		blockX = WIDTH/2-2;
		blockRotate = 0;
		PrintScore(score);
		DrawField();
	}
	
	//강의자료 p26-27의 플로우차트를 참고한다.
	timed_out = 0;//시간 초기화
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int sc = 0;
	int i,j;
	for (i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(block[currentBlock][blockRotate][i][j] == 1) 
			{f[blockY + i][blockX + j] = 1;
			if(blockY+i == HEIGHT-1)
				sc++;
		}
		}
	}
	return sc*10;
	//Block이 추가된 영역의 필드값을 바꾼다.
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
	int ans;
	int full=0;
	int i,j;
	ans=0;
	for(i=0; i< HEIGHT; i++)
	{
		full=1;
		for(j=0;j<WIDTH;j++){
			if(f[i][j]==0) {
			full=0;
			break;
			}
		}
	
	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	
	if(full) {

		for(int k = i-1; k>=1; k--)
		{
			for(j=0; j<WIDTH; j++)
			{
				field[k+1][j] = f[k][j];
			}
		}
		ans++; 
	}
	}
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
	return ans*ans*100;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
    while(CheckToMove(field,blockID,blockRotate,y+1,x))
		y++;
	
	DrawBlock(y,x,blockID,blockRotate,'/');
	// user code
}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate) {
		DrawBlock(y, x, blockID, blockRotate, ' ');
		DrawShadow(y, x, blockID, blockRotate);
}

void createRankList(){
	FILE *fp=fopen("rank.txt","r");
	int k;
	char str[NAMELEN];
	int num;
	if(fp==NULL)
		return;
	else
	{
		fscanf(fp,"%d",&num);
		for(int i=0; i< num; i++)
		{
			
			fscanf(fp,"%s %d",str,&k);
			NODE *new_node = (NODE*)malloc(sizeof(NODE));
			strcpy(new_node->name,str);
			new_node->score = k;
			
		if(i==0)
		{
			head=new_node;
			new_node->link=NULL;
		}
		else
		{
			NODE *now=head;
			if(head->score<=k)
			{new_node->link=head;
			head=new_node;
	        new_node->link=NULL;		
			}
			else
			{
				if(i==1)
				{
					new_node->link=NULL;
					head->link = new_node;
					
				}
				else
				{
				while(now->link!=NULL)
				{
				if(now->link->score <= k)
				{
					new_node->link = now->link;
					now->link=new_node;
					break;

				}
				else{
				if(now->link->link==NULL)
				{
					
					now->link->link=new_node;
					new_node->link=NULL;
					break;
				}
				}
					now=now->link;
				
				}
				}

				}

		}
		}

	}


fclose(fp);
	// user code
}

void rank(){
	// user code
	NODE*now=head;
	int max=0;
	while(now!=NULL)
	{
		max++;
		now=now->link;
	}


	
	char command;
	while(1){
	int x=0, y=0;
	int k=0;
	char s_name[NAMELEN];
	int deleterank = 0;
	clear();
	move(0,0);
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	command = wgetch(stdscr);
	if(command<'1' || command>'3')
	break;
	
	echo();
	switch (command) {
	
		case '1':
		
			printw("X: ");
			scanw("%d", &x);
			printw("Y: ");
			scanw("%d", &y);
			
			if(x==0)
				x=1;
			if(y==0||y>max)
				y=max;
			printw("	name	|	score\n");
			printw("-------------------------------\n");
			if(head==NULL || x>y)
				printw("\nsearch failure: no rank in the list\n");
			else
			{
				int i=1;
				now=head;
				while(now!=NULL)
				{
					if(i>=x&&i<=y)
						printw(" %-15s| %d\n", now->name, now->score);
					now=now->link;
					i++;
				}
				
			}
			getch();
			break;
		case '2':
			printw("input the name: ");
			scanw("%s",s_name);
			k=0;
			printw("    name    |   score\n");
            printw("-------------------------------\n");
			now=head;
			while(now!=NULL)
			{
				if (!strcmp(now->name,s_name))
				{
					printw(" %-15s| %d\n", now->name, now->score);
					k++;
				}
				now=now->link;
			}
			if(!k)
				printw("\nsearch failure: no name in the list\n");
			getch();
			break;
		case '3':
			printw("input the rank: ");
			scanw("%d", &deleterank);
			printw("\n");
			k=1;
			if(deleterank>0&&deleterank<=max)
			{
				if(deleterank==1)
				{
					NODE*delete=head;
					head=head->link;
					free(delete);
				}
				else
				{
					now=head;
					while(k<deleterank-1)
					{
						now=now->link;
						k++;
					}
					NODE*delete=now->link;
					now->link=now->link->link;
					free(delete);
				}
				printw("result: the rank deleted\n");
				max--;
				writeRankFile();
			}
			else
			printw("search failure: the rank not in the list\n");
			getch();
			break;
		default: break;
	
	}

	noecho();
	}
	

}

void writeRankFile(){
	// user code
	NODE*now=head;
	int max=0;
	while(now!=NULL)
	{
		max++;
		now=now->link;
	}

	FILE *fp=fopen("rank.txt","r");
	if(fp==NULL){
		fp=fopen("rank.txt","w");
		fprintf(fp,"%d\n",max);
	now=head;
	while(now!=NULL)
	{
		fprintf(fp,"%s %d\n",now->name,now->score);
		now=now->link;
	}

	}
	else
	{
		int tmp;
		if(fscanf(fp,"%d",&tmp)==max)
		{
			fclose(fp);
			return;
		}
		else
		{
			fclose(fp);
			fp=fopen("rank.txt","w");
			fprintf(fp,"%d\n",max);
			now=head;
			while(now!=NULL)
			{
			fprintf(fp,"%s %d\n",now->name,now->score);
			now=now->link;
			}

		}

	}


}

void newRank(int score){
	// user code
	NODE*now=head;
	int max=0;
	while(now!=NULL)
	{
		max++;
		now=now->link;
	}

	clear();
	move(0,0);
	char name[NAMELEN];
	printw("your name: ");
	echo();
	scanw("%s",name);
	noecho();
	
	NODE *new_node=(NODE*)malloc(sizeof(NODE));
	strcpy(new_node->name,name);
	new_node->score=score;
	

	if(max==0)
	{
		head=new_node;
	}
	else
	{
		if(head->score<=score)
		{
			head->link=new_node;
			new_node->link=NULL;
		}
		else if(head->link==NULL&&head->score>score)
		{
			new_node->link=NULL;
			head->link=new_node;
		}
		else
		{
			NODE *now=head;
			while(now->link!=NULL)
			{
			 if(now->link->score <= score)
			 {
			 new_node->link=now->link;
			 now->link=new_node;
			 break;
			 }
			 else
			 {
				if(now->link->link==NULL)
				{
					now->link->link=new_node;
					new_node->link=NULL;
					break;
				}
			 }

			now=now->link;
			}
		}

	}
	writeRankFile();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
	R_y=y; R_x=x;
	R_ID=blockID; R_rotate=blockRotate;
	DrawBlock(y,x,blockID,blockRotate,'R');
}

int recommend(RecNode *root){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(block[R_ID][R_rotate][i][j]==1&&R_y+i>-1)
			{	move(R_y+i+1,R_x+j+1);
				printw(".");
			}
			}
	}


	answernode=root;
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수
	root->lv=0;
	
	addtree(root);
	/*
	// user code
	while(answernode->lv>1)
	{
		answernode=answernode->parent;
	}
	DrawRecommend(answernode->recBlockY,answernode->recBlockX,answernode->curBlockID,answernode->recBlockRotate);
	max=answernode->score;
*/	
	return max;
}

void tree(RecNode *node)
{
	if(!node->lv)
	{
		node->score=0;
		node->parent=NULL;
		node->recBlockY=0;
		node->recBlockX=0;
		node->recBlockRotate=0;
		node->curBlockID=nextBlock[node->lv];
		for(int i=0; i<HEIGHT; i++)
		{
			for(int j=0; j<WIDTH;j++)
			{
				node->f[i][j]=field[i][j];
			}

		}

	}
	if(node->lv < VISIBLE_BLOCKS)
	{
		int i=0;
		while(i<CHILDREN_MAX)
		{
			node->c[i]=malloc(sizeof(RecNode));
			node->c[i]->lv=node->lv+1;
			node->c[i]->parent=node;
			node->c[i]->score=0;
			//node->c[i]->curBlockID=nextBlock[node->lv];
			tree(node->c[i]);
			i++;
		}
	}
	
}


void addtree(RecNode*node){
		if(node->lv==0)
			{
				for(int i=0; i<HEIGHT; i++)
			 {
             for(int j=0; j<WIDTH;j++)
             {
                 node->f[i][j]=field[i][j];
             }

			 }

			}
		int i=0;
		for(int rotate=0; rotate<blocknum[nextBlock[node->lv]]; rotate++)
			{ 
				int y=0;
				for(int x=-1; x<WIDTH; x++){
					if(CheckToMove(node->f,nextBlock[node->lv],rotate,y,x)==1){
			/*			for(int a=0; a<HEIGHT; a++)
					    {
							for(int b=0; b<WIDTH; b++)
							 {
                             node->c[i]->f[a][b]=node->f[a][b];
							 }
                     }
					}
					while(CheckToMove(node->f,nextBlock[node->lv],rotate,y,x)==1&&y<HEIGHT)y++;
					y--;
					node->c[i]->recBlockY=y;
					node->c[i]->recBlockX=x;
					node->c[i]->recBlockRotate=rotate;
					node->c[i]->curBlockID=nextBlock[node->c[i]->lv];
					//node->c[i]->score=node->score+AddBlockToField(node->c[i]->f,node->c[i]->curBlockID,node->recBlockRotate,node->c[i]->recBlockY,node->c[i]->recBlockX)+DeleteLine(node->c[i]->f);

					if(node->c[i]->score>answernode->score)
					answernode=node->c[i];
					if(node->c[i]->lv<VISIBLE_BLOCKS)
			*/		//addtree(node->c[i]);
					i++;
			
				}
		    }
			
			
	

}


void recommendedPlay(){
	// user code
	clear();
}
