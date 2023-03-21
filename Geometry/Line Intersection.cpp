pair<pdd,pll> intersect(pdd aa, pdd bb, pdd cc, pdd dd){
    ll a = ccw(aa,bb,cc), b = ccw(aa,bb,dd);
    ll c = ccw(cc,dd,aa), d = ccw(cc,dd,bb);

    // an: whether line intersects
    // pt: whether line intersects at one point
    // pnt: the intersection point(if one exists)

    ll r1 = sign(a)*sign(b), r2 = sign(c)*sign(d), an = 0, pt = 0;
    pdd pnt = {0,0};
    if(r1==0&&r2==0){
        if(aa>bb) swap(aa,bb);
        if(cc>dd) swap(cc,dd);
        if(aa<=dd&&cc<=bb){
            an = 1;
            if((aa.ff-bb.ff)*(cc.ss-dd.ss)==(aa.ss-bb.ss)*(cc.ff-dd.ff)){
                if(aa==dd&&bb>cc) pnt = aa, pt = 1;
                if(dd>aa&&bb==cc) pnt = bb, pt = 1;
            }
            else{
                if(aa==cc||aa==dd) pnt = aa, pt = 1;
                if(bb==cc||bb==dd) pnt = bb, pt = 1;
            }
        }
        else an = 0;
    }
    else if(r1<=0&&r2<=0){
        an = 1; pt = 1;
        double al = 1.0*abs(a)/abs(a-b);
        pnt = {cc.ff*(1-al)+dd.ff*al,cc.ss*(1-al)+dd.ss*al};
    }
    else an = 0;
    return {pnt,{an,pt}};
}
