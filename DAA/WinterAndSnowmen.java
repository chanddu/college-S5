public class WinterAndSnowmen {
    static final long MODULO = (long) (1e9 + 7);
 
    public int getNumber(int N, int M) {
        int p2 = 1;
        int bits = 0;
        while (N >= p2 || M >= p2) {
            p2 *= 2;
            ++bits;
        }
        long res = 0;
        for (int equalBits = 0; equalBits < bits; ++equalBits) {
            int[] ways = new int[1 << (equalBits + 2)];
            int[] nways = new int[1 << (equalBits + 2)];
            ways[0] = 1;
            for (int x = 1; x <= N || x <= M; ++x) {
                System.arraycopy(ways, 0, nways, 0, ways.length);
                int prefix = x >> (bits - equalBits);
                int toggles = ((x >> (bits - equalBits - 1)) & 1);
                if (x <= N) {
                    for (int old = 0; old < ways.length; ++old) {
                        int amt = ways[old];
                        if (amt != 0) {
                            int nxt = old ^ (prefix << 2) ^ (toggles << 1);
                            nways[nxt] += amt;
                            if (nways[nxt] >= MODULO) nways[nxt] -= MODULO;
                        }
                    }
                }
                if (x <= M) {
                    for (int old = 0; old < ways.length; ++old) {
                        int amt = ways[old];
                        if (amt != 0) {
                            int nxt = old ^ (prefix << 2) ^ toggles;
                            nways[nxt] += amt;
                            if (nways[nxt] >= MODULO) nways[nxt] -= MODULO;
                        }
                    }
                }
                int[] tmp = ways;
                ways = nways;
                nways = tmp;
            }
            res = (res + ways[1]) % MODULO;
        }
        return (int) res;
    }
}