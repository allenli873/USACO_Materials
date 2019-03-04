import java.io.FileNotFoundException;
import java.net.URL;
import java.util.Scanner;

public class RankCheck {
	public static void main(String[] args) throws Exception {
		String[] arr = new String[]{"open", "feb", "jan", "dec"};
		String[] div = new String[]{"bronze", "silver", "gold", "plat"};
		Scanner in = new Scanner(System.in);
		System.out.println("Enter in a full name");
		String str = in.nextLine();
//		System.out.println("Enter in graduation year");
//		String str2 = in.nextLine();
		for(int year = 19; year >= 16; year--) {
			for(int j = 0; j < 4; j++) {
				int a = j != 3 ? year : year - 1;
				for(int k = 2; k >= 0; k--) {
					try {
						URL url = new URL("http://usaco.org/current/data/" + arr[j] + a + "_" + div[k] + "_results.html");
						in = new Scanner(url.openStream());
						while(in.hasNextLine()) {
							String next = in.nextLine();
							if(next.contains(str)) {
								System.out.println(url.toString());
								System.out.println("Current Division: " + div[k + 1]);
								return;
							}
						}
					} catch(FileNotFoundException e) {
						continue;
					}
				}
			}
		}
		System.out.println("Could not find " + str + " in recent years");
	}
}
