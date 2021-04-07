import java.util.PriorityQueue;
import java.util.Comparator;
import java.util.Scanner;

public class Main {

    static class Data {
        int y;
        int result;
        Data(int y, int result) {
            this.y = y;
            this.result = result;
        }
    }

    public static void main(String[] args) {
        PriorityQueue<Data> queue = new PriorityQueue<>(new Comparator<Data>() {
            @Override
            public int compare(Data o1, Data o2) {
                return o2.y - o1.y;
            }
        });
        Scanner scanner = new Scanner(System.in);
        int m = scanner.nextInt();
        int f = 0;
        for (int i = 0; i < m; i++) {
            int y = scanner.nextInt();
            int res = scanner.nextInt();
            queue.offer(new Data(y, res));
            if (res == 0) {
                f++;
            }
        }
        scanner.close();

        int theta = 0;
        int max = 0;
        int scount = 0;                  // count the s
        int fcount = 0;
        for (int i = 1; i <= m; i++) {
            Data data = queue.poll();
            if (data.result == 1) {
                scount++;
            } else {
                fcount++;
            }
            if (!queue.isEmpty() && queue.peek().y == data.y) {
                continue;
            }
            int acc = scount + f - fcount;
            if (acc > max) {
                max = acc;
                theta = data.y;
            }
        }
        System.out.println(theta);

    }

}
