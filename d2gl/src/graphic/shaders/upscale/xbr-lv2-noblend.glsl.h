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
"\n#define CoefLuma vec3(0.2126,0.7152,0.0722)\n"
"vec4 v(vec4 x,vec4 w)"
"{"
  "return vec4(abs(x-w));"
"}"
"vec4 m(vec4 x,vec4 v)"
"{"
  "return vec4(notEqual(x,v));"
"}"
"vec4 m(vec4 x,vec4 w,vec4 y,vec4 u,vec4 m,vec4 z,vec4 g,vec4 F)"
"{"
  "return v(x,w)+v(x,y)+v(u,m)+v(u,z)+4.*v(g,F);"
"}"
"\n#define P(x)texture(u_Texture,x).rgb\n"
"void main()"
"{"
  "vec2 u=v_TexCoord,n=u_RelSize;"
  "vec4 x=u.xxxy+vec4(-n.x,0,n.x,-2.*n.y),g=u.xxxy+vec4(-n.x,0,n.x,-n.y),l=u.xxxy+vec4(-n.x,0,n.x,0),s=u.xxxy+vec4(-n.x,0,n.xy),C=u.xxxy+vec4(-n.x,0,n.x,2.*n.y),F=u.xyyy+vec4(-2.*n.x,-n.y,0,n.y),a=u.xyyy+vec4(2.*n.x,-n.y,0,n.y),y,d,z,w,e,b,i,r;"
  "bvec4 T,o;"
  "vec4 V,A,D;"
  "vec2 B=fract(u*u_TexSize);"
  "vec3 E=P(x.xw),G=P(x.yw),H=P(x.zw),I=P(g.xw),J=P(g.yw),K=P(g.zw),L=P(l.xw),M=P(l.yw),N=P(l.zw),O=P(s.xw),Q=P(s.yw),R=P(s.zw),S=P(C.xw),U=P(C.yw),W=P(C.zw),X=P(F.xy),Y=P(F.xz),Z=P(F.xw),c=P(a.xy),f=P(a.xz),h=P(a.xw);"
  "vec4 j=CoefLuma*mat4x3(J,L,Q,N),k=CoefLuma*mat4x3(K,I,O,R),p=CoefLuma*mat4x3(M,M,M,M),q=j.yzwx,t=j.wxyz,ax=k.zwxy,aw=j.zwxy,ay=k.wxyz,at=CoefLuma*mat4x3(h,H,X,S),an=CoefLuma*mat4x3(W,c,E,Z),au=CoefLuma*mat4x3(U,f,G,Y),aa=vec4(1,-1,-1,1),ab=vec4(1,1,-1,-1),ak=vec4(1.5,.5,-.5,.5),ai=vec4(1,-1,-1,1),ad=vec4(.5,2,-.5,-2),az=vec4(1,1,-.5,0),ag=vec4(1,-1,-1,1),al=vec4(2,.5,-2,-.5),aF=vec4(2,0,-1,.5);"
  "V=vec4(greaterThan(aa*B.y+ab*B.x,ak));"
  "A=vec4(greaterThan(ai*B.y+ad*B.x,az));"
  "D=vec4(greaterThan(ag*B.y+al*B.x,aF));"
  "e=m(p,t)*m(p,aw);"
  "b=m(p,ax)*m(q,ax);"
  "i=m(p,k)*m(j,k);"
  "vec4 ap=m(p,k,ax,ay,au,au.yzwx,aw,t),ae=m(aw,q,an,t,at,j,p,ay);"
  "y=step(ap,ae)*e;"
  "d=step(ap+vec4(.1),ae)*step(vec4(.5),e);"
  "z=step(2.*v(t,ax),v(aw,k))*b*d;"
  "w=step(2.*v(aw,k),v(t,ax))*i*d;"
  "T=bvec4(d*(V+z*A)+w*D);"
  "o=lessThanEqual(v(p,t),v(p,aw));"
  "vec3 aM=T.x?"
    "o.x?"
      "N:"
      "Q:"
    "T.y?"
      "o.y?"
        "J:"
        "N:"
      "T.z?"
        "o.z?"
          "L:"
          "J:"
        "M,aA=T.w?"
    "o.w?"
      "Q:"
      "L:"
    "T.z?"
      "o.z?"
        "L:"
        "J:"
      "T.y?"
        "o.y?"
          "J:"
          "N:"
        "M;"
  "vec2 aB=abs(CoefLuma*mat2x3(aM,aA)-p.xy);"
  "FragColor=vec4(mix(aM,aA,step(aB.x,aB.y)),1);"
"}"
"\n#endif"