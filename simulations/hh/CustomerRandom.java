public class CustomerRandom {
    public static void main(String[] args) {
        for (int i = 0; i < 100; i++) {
            System.out.println(5*GetProbality());
        }
    }

    public static double GetProbality() {
        double ran = Math.random();
        switch ((int) Math.floor(ran * 4)) {
            case 0:
                return Poisson();
            case 1:
                return Uniform();
            case 2:
                return Bimodal();
        }
        return Normal();
    }

    public static double Poisson() {
        double random = Math.random();
        double p = 1;
        double L = Math.exp(-1);
        while (true) {
            p *= random;
            if (p <= L) {
                return p;
            }
        }
    }

    public static double Normal() {
        double random = Math.random();
        double random11 = random * 2 - 1;

        double sd = 1;
        double mean = 0;
        double variance = 1;
        double M = 1 / (sd * Math.sqrt(Math.PI * 2));
        double x = random11 - mean;
        double w = Math.exp(-x * x / (2 * variance));
        return M * w;
    }

    public static double Uniform() {
        return Math.random();

    }

    public static double Bimodal() {
        double random = Math.random();
        double p = 1;
        double N = 3628800; // n!
        double x = Math.floor(random * 9);
        double px = Math.pow(p, x);
        double qx = Math.pow(1 - p, 10 - x);
        double M = 1;
        for (int i = 1; i <= x; i++) {
            M = M * i * (10 - i);
        }
        return (N / M) * px * qx;
    }
	

}
