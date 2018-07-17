class Point {
    long x;
    long y;

    public Point(long x, long y) {
        this.x = x;
        this.y = y;
    }

    public long distance2(Point point) {
        long dx = x - point.x;
        long dy = y - point.y;
        return dx * dx + dy * dy;
    }

    public Point add(Point point) {
        return new Point(x + point.x, y + point.y);
    }

    public Point subtract(Point point) {
        return new Point(x - point.x, y - point.y);
    }

    public long magnitude2() {
        return x * x + y * y;
    }

    public double magnitude() {
        return Math.hypot(x, y);
    }

    public long dotProduct(Point point) {
        return x * point.x + y * point.y;
    }

    public long crossProduct(Point point) {
        return point.x * y - point.y * x;
    }

    public boolean equals(Point anotherPoint) {
        return x == anotherPoint.x && y == anotherPoint.y;
    }
}