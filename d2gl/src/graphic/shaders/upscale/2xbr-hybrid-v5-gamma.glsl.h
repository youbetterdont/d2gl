#pragma once

"#ifdef VERTEX\n"
"layout(location=0) in vec2 Position;"
"layout(location=1) in vec2 TexCoord;"
"uniform mat4 u_MVP;"
"out vec2 v_TexCoord;"
"void main()"
"{"
  "gl_Position=u_MVP*vec4(Position,0,1);"
  "v_TexCoord=TexCoord;"
"}"
"\n#elif FRAGMENT\n"
"layout(location=0) out vec4 FragColor;layout(std140) uniform ubo_Metrics{vec2 u_OutSize;vec2 u_TexSize;vec2 u_RelSize;};"
"uniform sampler2D u_Texture;"
"in vec2 v_TexCoord;"
"\n#define mul(a,b)(b*a)\n"
"const vec4 v=vec4(15);"
"const mat3x3 u=mat3x3(.299,.587,.114,-.169,-.331,.499,.499,-.418,-.0813),n=mat3x3(48.*u[0],7.*u[1],6.*u[2]);"
"const vec4 x=vec4(.5);"
"vec4 l(vec4 m,vec4 w)"
"{"
  "return vec4(abs(m-w));"
"}"
"bvec4 m(vec4 m,vec4 v)"
"{"
  "return lessThan(l(m,v),vec4(15));"
"}"
"bvec4 t(vec4 m,vec4 v)"
"{"
  "return lessThan(l(m,v),vec4(2));"
"}"
"bvec4 f(vec4 m,vec4 v)"
"{"
  "return lessThan(l(m,v),vec4(5));"
"}"
"vec4 f(vec4 m,vec4 v,vec4 x,vec4 n,vec4 w,vec4 y,vec4 u,vec4 b)"
"{"
  "return l(m,v)+l(m,x)+l(n,w)+l(n,y)+4.*l(u,b);"
"}"
"bvec4 s(bvec4 m,bvec4 w)"
"{"
  "return bvec4(m.x&&w.x,m.y&&w.y,m.z&&w.z,m.w&&w.w);"
"}"
"bvec4 b(bvec4 m,bvec4 w)"
"{"
  "return bvec4(m.x||w.x,m.y||w.y,m.z||w.z,m.w||w.w);"
"}"
"\n#define P(x)texture(u_Texture,x).rgb\n"
"void main()"
"{"
  "vec2 v=v_TexCoord,w=u_RelSize;"
  "vec4 u=v.xxxy+vec4(-w.x,0,w.x,-2.*w.y),y=v.xxxy+vec4(-w.x,0,w.x,-w.y),a=v.xxxy+vec4(-w.x,0,w.x,0),z=v.xxxy+vec4(-w.x,0,w.xy),c=v.xxxy+vec4(-w.x,0,w.x,2.*w.y),d=v.xyyy+vec4(-2.*w.x,-w.y,0,w.y),g=v.xyyy+vec4(2.*w.x,-w.y,0,w.y);"
  "bvec4 i,e,o,T,r,A,C,B,D,E,F;"
  "vec4 V,G,H,I;"
  "vec2 J=fract(v*u_TexSize);"
  "vec3 K=P(u.xw),L=P(u.yw),M=P(u.zw),N=P(y.xw),O=P(y.yw),Q=P(y.zw),R=P(a.xw),S=P(a.yw),U=P(a.zw),W=P(z.xw),X=P(z.yw),Y=P(z.zw),Z=P(c.xw),h=P(c.yw),j=P(c.zw),k=P(d.xy),p=P(d.xz),q=P(d.xw),ax=P(g.xy),an=P(g.xz),am=P(g.xw);"
  "vec4 aw=mul(mat4x3(O,R,X,U),n[0]),ay=mul(mat4x3(Q,N,W,Y),n[0]),at=mul(mat4x3(S,S,S,S),n[0]),az=aw.yzwx,al=aw.wxyz,av=ay.zwxy,ab=aw.zwxy,ai=ay.wxyz,ae=mul(mat4x3(am,M,k,Z),n[0]),aD=mul(mat4x3(j,ax,K,q),n[0]),aJ=mul(mat4x3(h,an,L,p),n[0]),aE=aJ.yzwx,ag=vec4(1,-1,-1,1),ac=vec4(1,1,-1,-1),ad=vec4(1.5,.5,-.5,.5),ar=vec4(1,-1,-1,1),au=vec4(.5,2,-.5,-2),aA=vec4(1,1,-.5,0),aB=vec4(1,-1,-1,1),aC=vec4(2,.5,-2,-.5),aF=vec4(2,0,-1,.5);"
  "V=ag*J.y+ac*J.x;"
  "G=ar*J.y+au*J.x;"
  "H=aB*J.y+aC*J.x;"
  "bvec4 aS=s(not(m(ab,aJ)),not(m(ab,aD))),ao=s(not(m(al,aE)),not(m(al,ae))),aG=s(not(m(ab,az)),not(m(ab,av))),aH=s(not(m(al,aw)),not(m(al,ay))),aK=s(m(at,ai),b(ao,aS)),aT=b(aH,b(aG,b(aK,b(m(at,av),m(at,ay)))));"
  "r=s(notEqual(at,al),s(notEqual(at,ab),aT));"
  "A=s(notEqual(at,av),notEqual(az,av));"
  "C=s(notEqual(at,ay),notEqual(aw,ay));"
  "vec4 aV=smoothstep(ad-x,ad+x,V),aa=smoothstep(aA-x,aA+x,G),aL=smoothstep(aF-x,aF+x,H);"
  "i=s(lessThan(f(at,ay,av,ai,aJ,aE,ab,al)+3.5,f(ab,az,aD,al,ae,aw,at,ai)),r);"
  "e=s(lessThanEqual(2.*l(al,av),l(ab,ay)),A);"
  "o=s(greaterThanEqual(l(al,av),2.*l(ab,ay)),C);"
  "F=s(i,bvec4(aV));"
  "D=s(i,s(e,bvec4(aa)));"
  "E=s(i,s(o,bvec4(aL)));"
  "T=lessThanEqual(l(at,al),l(at,ab));"
  "vec3 aM=S,aO,aR,aX,aN,aU,aQ,aW,aY,ap;"
  "aO=L;"
  "aR=O;"
  "aU=S;"
  "aX=X;"
  "aN=h;"
  "aQ=aR-aO;"
  "aW=aU-aR;"
  "aY=aX-aU;"
  "ap=aN-aX;"
  "vec3 ah=(7.*(aW+aY)-3.*(aQ+ap))/16.,aZ;"
  "aZ.x=aU.x<.5?"
    "2.*aU.x:"
    "2.*(1.-aU.x);"
  "aZ.y=aU.y<.5?"
    "2.*aU.y:"
    "2.*(1.-aU.y);"
  "aZ.z=aU.z<.5?"
    "2.*aU.z:"
    "2.*(1.-aU.z);"
  "aZ=min(aZ,.65*abs(aW));"
  "aZ=min(aZ,.65*abs(aY));"
  "ah=clamp(ah,-aZ,aZ);"
  "vec3 aI=(2.*J.y-1.)*ah+aU;"
  "aO=p;"
  "aR=R;"
  "aU=aI;"
  "aX=U;"
  "aN=an;"
  "aQ=aR-aO;"
  "aW=aU-aR;"
  "aY=aX-aU;"
  "ap=aN-aX;"
  "ah=(7.*(aW+aY)-3.*(aQ+ap))/16.;"
  "aZ.x=aU.x<.5?"
    "2.*aU.x:"
    "2.*(1.-aU.x);"
  "aZ.y=aU.y<.5?"
    "2.*aU.y:"
    "2.*(1.-aU.y);"
  "aZ.z=aU.z<.5?"
    "2.*aU.z:"
    "2.*(1.-aU.z);"
  "aZ=min(aZ,.65*abs(aW));"
  "aZ=min(aZ,.65*abs(aY));"
  "ah=clamp(ah,-aZ,aZ);"
  "vec3 aq=(2.*J.x-1.)*ah+aU;"
  "B=b(D,b(E,F));"
  "float aj=0.;"
  "vec3 ak;"
  "vec4 aP=mix(at,al,i);"
  "bool af=false;"
  "bvec4 as;"
  "ak=all(f(aP,at))?"
    "(af=true,aM=aq):"
    "(aM=S);"
  "as=s(bvec4(af),t(at,mix(al,ab,T)));"
  "vec4 bv=vec4(F)*aV,bx=vec4(D)*aa,bw=vec4(E)*aL,bk=max(max(bx,bw),bv);"
  "if(B.x)"
    "{"
      "ak=T.x?"
        "U:"
        "X;"
      "aj=bk.x;"
      "if(as.x)"
        "ak=aM=aq;"
      "else "
         "aM=S;"
    "}"
  "else "
     "if(B.y)"
      "{"
        "ak=T.y?"
          "O:"
          "U;"
        "aj=bk.y;"
        "if(as.y)"
          "ak=aM=aq;"
        "else "
           "aM=S;"
      "}"
    "else "
       "if(B.z)"
        "{"
          "ak=T.z?"
            "R:"
            "O;"
          "aj=bk.z;"
          "if(as.z)"
            "ak=aM=aq;"
          "else "
             "aM=S;"
        "}"
      "else "
         "if(B.w)"
          "{"
            "ak=T.w?"
              "X:"
              "R;"
            "aj=bk.w;"
            "if(as.w)"
              "ak=aM=aq;"
            "else "
               "aM=S;"
          "}"
  "FragColor=vec4(clamp(mix(aM,ak,aj),0.,1.),1);"
"}"
"\n#endif"