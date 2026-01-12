import java.io.*;
import java.net.*;
import java.util.*;

public class TcpClient {
    public static void main(String[] args) {
        try {
            Socket s = new Socket("localhost", 5000);
            Scanner user = new Scanner(System.in);
            Scanner in = new Scanner(s.getInputStream());
            PrintWriter out = new PrintWriter(s.getOutputStream(), true);

            System.out.print("Enter file name: ");
            String fileName = user.nextLine();
            out.println(fileName);

            System.out.println("\n--- File Contents ---");
            while (in.hasNextLine()) {
                System.out.println(in.nextLine());
            }

            s.close();
            user.close();
            in.close();
            out.close();
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}

/*
 * Sample Input:
 * Enter file name: hello.txt
 * 
 * Sample Output:
 * --- File Contents ---
 * Hello, this is a test file.
 * This is another line.
 */