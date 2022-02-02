#pragma once

class Interpolate {
    public:
    //regular interplolation (time relevant)
    static double lerp(double start, double end, double time) {
        return start + (end - start) * time;
    };

    //lerp between two points, no time involved
    static double lerp2(double x, double x1, double y1, double x2, double y2) {
        return y1 + (x - x1) * ((y2 - y1)/ (x2-x1));
    };

    static double slerp() {
        throw "Not Implemented idot";
    };
};