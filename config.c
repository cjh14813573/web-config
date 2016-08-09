/* Change this if the SERVER_NAME environment variable does not report
	the true name of your web server. */
#if 1
#define SERVER_NAME CTT2000E_embedded_server
#endif
#if 0
#define SERVER_NAME "www.ctt2000e.com"
#endif

#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"

#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include "inifile.h"

void comset(char *s,int *pDatabuf)
{
	char cfg[7][10];
	sprintf(cfg[0],"%d",pDatabuf[0]);//任务
	switch(pDatabuf[1])//波特率
	{
		case 0:
			sprintf(cfg[1],"%d",600);
			break;
		case 1:
			sprintf(cfg[1],"%d",1200);
			break;
		case 2:
			sprintf(cfg[1],"%d",2400);
			break;
		case 3:
			sprintf(cfg[1],"%d",4800);
			break;
		case 4:
			sprintf(cfg[1],"%d",9600);
			break;
		case 5:
			sprintf(cfg[1],"%d",19200);
			break;
		case 6:
			sprintf(cfg[1],"%d",38400);
			break;
		default:
			break;
	}
	switch(pDatabuf[2])//数据位
	{
		case 0:
			sprintf(cfg[2],"7");
			break;
		case 1:
			sprintf(cfg[2],"8");
			break;
		case 2:
			sprintf(cfg[2],"5");
			break;
		default:
			break;
	}
	switch(pDatabuf[3])//校验位
	{
		case 0:
			sprintf(cfg[3],"e");
			break;
		case 1:
			sprintf(cfg[3],"o");
			break;
		case 2:
			sprintf(cfg[3],"n");
			break;
		default:
			break;
	}
	switch(pDatabuf[4])//停止位
	{
		case 0:
			sprintf(cfg[4],"1");
			break;
		case 1:
			sprintf(cfg[4],"1.5");
			break;
		case 2:
			sprintf(cfg[4],"2");
			break;
		default:
			break;
	}
	sprintf(cfg[5],"0");//不用了
	sprintf(cfg[6],"%d",pDatabuf[6]);//设备数
	sprintf(s,"%s,%s,%s,%s,%s,%s,%s",cfg[0],cfg[1],cfg[2],cfg[3],cfg[4],cfg[5],cfg[6]);
}

int cgiMain() {
	int i=0;
	char *cfgFile="/app/RTUcfg.ini";
	char *section;
	char *key;
	char com_key[10];
	char temp[96]={0};


	char address[20]={0};//站地址
	if(cgiFormString("rtuID",address,20)!=cgiFormSuccess){
		goto FAIL;
	}
	section="RTUAddrdelaytime";
	key="Address";
	write_profile_string(section,key,address,cfgFile);

	char ip[20]={0};//ip地址
	if(cgiFormString("ip",ip,20)!=cgiFormSuccess){
		goto FAIL;
	}
	section="RTUNetset";
	key="IP";
	write_profile_string(section,key,ip,cfgFile);

	char mask[20]={0};//子网掩码
	if(cgiFormString("mask",mask,20)!=cgiFormSuccess){
		goto FAIL;
	}
	section="RTUNetset";
	key="Netmask";
	write_profile_string(section,key,mask,cfgFile);

	char gate[20]={0};//网关
	if(cgiFormString("gate",gate,20)!=cgiFormSuccess){
		goto FAIL;
	}
	section="RTUNetset";
	key="Gateway";
	write_profile_string(section,key,gate,cfgFile);

	int AI[16];//AI
	char AI_name[20];
	for(i=0;i<16;i++){
		sprintf(AI_name,"AI_%d",i+1);
		if(cgiFormInteger(AI_name,&AI[i],255)!=cgiFormSuccess){
			goto FAIL;
		}
	}
	sprintf(temp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",AI[0],AI[1],AI[2],AI[3],AI[4],AI[5],AI[6],AI[7],AI[8],AI[9],AI[10],AI[11],AI[12],AI[13],AI[14],AI[15]);
	section="RTUAISet";
	key="AI";
	write_profile_string(section,key,temp,cfgFile);

	
	int DI[16];//DI
	char DI_name[20];
	for(i=0;i<16;i++){
		sprintf(DI_name,"DI_%d",i+1);
		if(cgiFormInteger(DI_name,&DI[i],255)!=cgiFormSuccess){
			goto FAIL;
		}
	}
	sprintf(temp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",DI[0],DI[1],DI[2],DI[3],DI[4],DI[5],DI[6],DI[7],DI[8],DI[9],DI[10],DI[11],DI[12],DI[13],DI[14],DI[15]);
	section="RTUDISet";
	key="DI";
	write_profile_string(section,key,temp,cfgFile);

	int DO[6];//DO
	char DO_name[20];
	for(i=0;i<6;i++){
		sprintf(DO_name,"DO_%d",i+1);
		if(cgiFormInteger(DO_name,&DO[i],255)!=cgiFormSuccess){
			goto FAIL;
		}
	}
	sprintf(temp,"%d,%d,%d,%d,%d,%d",DO[0],DO[1],DO[2],DO[3],DO[4],DO[5]);
	section="RTUDOSet";
	key="DO";
	write_profile_string(section,key,temp,cfgFile);

	int DB[7];//DB
	if(cgiFormInteger("dbgroup",&DB[0],0)!=cgiFormSuccess){
		goto FAIL;
	}
	char DB_name[20];
	for(i=1;i<=6;i++){
		sprintf(DB_name,"db%dnum",i);
		if(cgiFormInteger(DB_name,&DB[i],255)!=cgiFormSuccess){
			goto FAIL;
		}
	}
	sprintf(temp,"%d,%d,%d,%d,%d,%d,%d",DB[0],DB[1],DB[2],DB[3],DB[4],DB[5],DB[6]);
	section="RTUDBSet";
	key="DB";
	write_profile_string(section,key,temp,cfgFile);

	int COM[7];//串口
	char COM_name[20];
	for(i=1;i<=7;i++){
		sprintf(COM_name,"com%dtask",i);
		if(cgiFormInteger(COM_name,&COM[0],255)!=cgiFormSuccess){
			goto FAIL;
		}
		sprintf(COM_name,"com%dbaud",i);
		if(cgiFormInteger(COM_name,&COM[1],0)!=cgiFormSuccess){
			goto FAIL;
		}
		sprintf(COM_name,"com%ddata",i);
		if(cgiFormInteger(COM_name,&COM[2],0)!=cgiFormSuccess){
			goto FAIL;
		}
		sprintf(COM_name,"com%dcheck",i);
		if(cgiFormInteger(COM_name,&COM[3],0)!=cgiFormSuccess){
			goto FAIL;
		}
		sprintf(COM_name,"com%dstop",i);
		if(cgiFormInteger(COM_name,&COM[4],0)!=cgiFormSuccess){
			goto FAIL;
		}
		sprintf(COM_name,"com%dnum",i);
		if(cgiFormInteger(COM_name,&COM[6],1)!=cgiFormSuccess){
			goto FAIL;
		}
		comset(temp,COM);
		section="RTUCOMSet";
		sprintf(com_key,"com%d",i);
		write_profile_string(section,com_key,temp,cfgFile);
	}
	goto END;



	FAIL:
		cgiHeaderLocation("../config_error.html");
		return 1;

	END:
		printf("Content-type: text/html\r\n\r\n");
		printf("<html>");
		printf("<head>");
		printf("    <meta charset=\"utf-8\" content=\"text/html\">");
		printf("    <title>");
		printf("        ctt-2000e动环设备");
		printf("    </title>");
		printf("</head>");
		printf("<body style=\"background:#1782dd\">");
		printf("<div id=\"all\" style=\"width:500px;margin:250px auto;color:#fff;font-size:30px;text-align:center;line-height:60px;\">");
		printf("    设置成功<br>系统将在 <i id=\"time\" style=\"font-size:45px;\">5</i> 秒后重启");
		printf("</div>");
		printf("<script type=\"text/javascript\">");
		printf("    var id_of_time=setInterval(setTime,1000);");
		printf("    setTimeout(close,5000);");
		printf("    function setTime(){");
		printf("        var lastTime=document.getElementById(\"time\");");
		printf("        var number=lastTime.innerHTML;");
		printf("        number=number-1;");
		printf("        lastTime.innerHTML=number;");
		printf("    }");
		printf("    function close(){");
		printf("	clearInterval(id_of_time);");
		printf("	var all=document.getElementById(\"all\");");
		printf("	all.innerHTML=\"系统重启中，请稍后点此重试连接\";");
		printf("	all.onclick=function(){");
		printf("	    window.open(\"http://\"+location.hostname+\":\"+location.port,\"_self\",\"\");");
		printf("        };");
		printf("    }");
		printf("</script>");
		printf("</body>");
		printf("</html>");
		
		sleep(1);
		system("/sbin/reboot");
		return 0;
}
	
