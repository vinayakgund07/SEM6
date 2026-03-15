import java.i.o*;
import javax.servlet.*;
import javax.servlet.http.*;

public class WelcomeServlet extends HttpServlet{
	public void doGet(HttpServletRequest request,HttpServletResponse response)
		throws ServletException,IOException{
		response.setContentType("text/html");
		PrintWriter out=response.getWriter();

		out.println("<html><body>");
		out.println("<h2>Welcome to Java Servlet</h2>");
		out.println("</body></html>");
	}
}

