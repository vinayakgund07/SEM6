class EvenOdd implements Runnable{
	int type;
	EvenOdd(int type){
		this.type=type;
	}

	public void run(){
		for(int i=1;i<=20;i++)
		{
			if(type==0 && i%2==0)
			{
				System.out.println("Even:"+i);
			}

			if(type==1 && i%2!=0)
			{
				System.out.println("Odd:"+i);
			}
		}
	}
public static void main(String[] args)
{
	Thread evenThread=new Thread(new EvenOdd(0));
	Thread oddThread=new Thread(new EvenOdd(1));
	evenThread.start();
	oddThread.start();
}
}
