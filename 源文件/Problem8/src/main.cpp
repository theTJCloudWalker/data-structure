#include <iostream>
#include"Graphmtx.h"

void menu(){
	std::cout<< "**            电网造价模拟系统           **"<< std::endl;
	std::cout<< "========================================="<< std::endl;
	std::cout<< "**            A --- 创建电网顶点         **"<< std::endl;
	std::cout<< "**            B --- 添加电网的边         **"<< std::endl;
	std::cout<< "**            C --- 构造最小生成树        **"<< std::endl;
	std::cout<< "**            D --- exit                  **"<< std::endl;
}

int main()
{
#ifdef WIN32
	system("chcp 65001");
#endif
	menu();
	Graphmtx<std::string, int> p;
	std::cout<<std::endl;
	//std::cout<<"初始化电网系统:"<< std::endl;
	//std::cin >> p;
	std::string start;
	bool con=true;
	while(con){
		std::cout<<"请选择操作:";
		char option;
		std::cin >> option;
		switch(option){
			case 'A':{
				int num;
				std::cout<<"请输入顶点的个数:";
				std::cin>>num;
				std::string vertex;
				std::cout<<"请依次输入各顶点的名称:"<<std::endl;
				for(int i=0;i<num;i++){
					std::cin>>vertex;
					p.InsertVertex(vertex);
				}
				break;
			}
			case 'B':{
				int num;
				std::cout<<"请输入边的个数:";
				std::cin>>num;
				std::string vertex1,vertex2;
				int cost = 0;
				std::cout<<"请依次输入各顶点的名称:"<<std::endl;
				for(int i=0;i<num;i++){
					std::cin>>vertex1>>vertex2>>cost;
					int v1=p.Find(vertex1);
					int v2=p.Find(vertex2);
					if(v1!=-1&&v2!=-1){
						p.InsertEdge(v1,v2,cost);
					}
				}
				break;
			}
			case 'C':{
				if(p.NumberOfVertices()>1){
					std::cout<<"请输入起始顶点:";
	      			std::cin>>start;
					std::cout<<"最小生成树的顶点及边为:";
	            	p.Prim(start);
				}
				else if(p.NumberOfVertices()==1){
        			std::cout << "只有一个顶点，无法生成最小生成树" << std::endl;
				}
				break;
			}
			case 'D':{
				con=false;
				break;
			}
			default: {
				std::cout << "Error input" << std::endl;
				break;
			}
		}
	}


	/*std::cout<<"请输入起始顶点:";
	std::cin>>start;
	std::cout<<"生成Prim最小生成树!"<<std::endl;
	std::cout<<"最小生成树的顶点及边为:";
	p.Prim(start);*/

	std::cout << p;
	std::cout << "Hello world!" << std::endl;

	system("pause");
	return 0;
}