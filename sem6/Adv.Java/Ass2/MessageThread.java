class MessageThread implements Runnable{
	public void run(){
		for(int i=1;i<=5;i++)
		{
			System.out.println("Hello");
		}
	}
public static void main(String[] args)
{
	MessageThread mt=new MessageThread();
	Thread t=new Thread(mt);
	t.start();
}
}
