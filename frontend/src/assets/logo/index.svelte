<script lang="ts">
  import imageArrow from "./white_arrow.png";
  import imageH from "./H.png"
  import imageHa from "./Ha.png"
  import imageHac from "./Hac.png"
  import imageHack from "./Hack.png"
  import imageHackH from "./HackH.png"
  import imageHackHa from "./HackHa.png"
  import imageHackHac from "./HackHac.png"
  import imageHackHack from "./HackHack.png"
  import imageHackHackR from "./HackHackR.png"
  import imageHackHackRe from "./HackHackRe.png"
  import imageHackHackRev from "./HackHackRev.png"
  import imageHackHackRevo from "./HackHackRevo.png"
  import imageHackHackRevol from "./HackHackRevol.png"
  import imageHackHackRevolu from "./HackHackRevolu.png"
  import imageHackHackRevolut from "./HackHackRevolut.png"
  import imageHackHackRevoluti from "./HackHackRevoluti.png"
  import imageHackHackRevolutio from "./HackHackRevolutio.png"
  import imageHackHackRevolution from "./HackHackRevolution.png"
</script>

<style lang="scss">
  $delayGap: 0.05s;
  $scaleFactor: 4;

  .container {
    position: fixed;
  }

  .logo {
    padding-top: 3.2em;
    display: flex;
    flex-direction: column;
    position: relative;
  }

  .line1, .line2 {
    // Top space space
    display: flex;
    gap: 2em;
    padding-left: 6em;
  }

  .line2 {
    margin-left: 1em;
  }

  .hack1, .hack2, .revolutionLine {
    // Character spacing
    display: flex;
  }

  .divArrow {
    position: absolute;
    top: 50px;
    left: 0;
  }

  .imageArrow {
    height: 150px;
  }
  
  .divH,
  .divHa,
  .divHac,
  .divHack,
  .divHackH,
  .divHackHa,
  .divHackHac,
  .divHackHack,
  .divHackHackR,
  .divHackHackRe,
  .divHackHackRev,
  .divHackHackRevo,
  .divHackHackRevol,
  .divHackHackRevolu,
  .divHackHackRevolut,
  .divHackHackRevoluti,
  .divHackHackRevolutio,
  .divHackHackRevolution {
    display: flex;
    align-items: flex-end;
    animation-name: move;
    animation-duration: 2s;
    animation-iteration-count: infinite;
    image-rendering: pixelated;
    image-rendering: -moz-crisp-edges;
    image-rendering: crisp-edges;
  }

  .imageH { width: 12px * $scaleFactor }
  .imageHa { width: 9px * $scaleFactor }
  .imageHac { width: 9px * $scaleFactor }
  .imageHack { width: 9px * $scaleFactor }
  .imageHackH { width: 12px * $scaleFactor }
  .imageHackHa { width: 9px * $scaleFactor }
  .imageHackHac { width: 9px * $scaleFactor }
  .imageHackHack { width: 9px * $scaleFactor }
  .imageHackHackR { width: 16px * $scaleFactor }
  .imageHackHackRe { width: 13px * $scaleFactor }
  .imageHackHackRev { width: 13px * $scaleFactor }
  .imageHackHackRevo { width: 13px * $scaleFactor }
  .imageHackHackRevol { width: 5px * $scaleFactor }
  .imageHackHackRevolu { width: 12px * $scaleFactor }
  .imageHackHackRevolut { width: 13px * $scaleFactor }
  .imageHackHackRevoluti { width: 5px * $scaleFactor }
  .imageHackHackRevolutio { width: 13px * $scaleFactor }
  .imageHackHackRevolution { width: 13px * $scaleFactor }

  .divH {animation-delay: $delayGap * 1;}
  .divHa {animation-delay: $delayGap * 2;}
  .divHac {animation-delay: $delayGap * 3;}
  .divHack {animation-delay: $delayGap * 4;}
  .divHackH {animation-delay: $delayGap * 5;}
  .divHackHa {animation-delay: $delayGap * 6;}
  .divHackHac {animation-delay: $delayGap * 7;}
  .divHackHack {animation-delay: $delayGap * 8;}
  .divHackHackR {animation-delay: $delayGap * 9;}
  .divHackHackRe {animation-delay: $delayGap * 10;}
  .divHackHackRev {animation-delay: $delayGap * 11;}
  .divHackHackRevo {animation-delay: $delayGap * 12;}
  .divHackHackRevol {animation-delay: $delayGap * 13;}
  .divHackHackRevolu {animation-delay: $delayGap * 14;}
  .divHackHackRevolut {animation-delay: $delayGap * 15;}
  .divHackHackRevoluti {animation-delay: $delayGap * 16;}
  .divHackHackRevolutio {animation-delay: $delayGap * 17;}
  .divHackHackRevolution {animation-delay: $delayGap * 18;}

  @keyframes move {
    0% {
        transform: translateY(0);
    }
    10% {
        transform: translateY(-.5em);
    }
    20%, 100% {
        transform: translateY(0);
    }
  }
</style>

<div class="container">
  <div class="logo">
    <div class="divArrow">
      <img class="imageArrow" src="{imageArrow}" />
    </div>
    <div class="line1">
      <div class="hack1">
        <div class="divH"><img class="imageH" src="{imageH}" /></div>
        <div class="divHa"><img class="imageHa" src="{imageHa}" /></div>
        <div class="divHac"><img class="imageHac" src="{imageHac}" /></div>
        <div class="divHack"><img class="imageHack" src="{imageHack}" /></div>
      </div>
      <div class="hack2">
        <div class="divHackH"><img class="imageHackH" src="{imageHackH}" /></div>
        <div class="divHackHa"><img class="imageHackHa" src="{imageHackHa}" /></div>
        <div class="divHackHac"><img class="imageHackHac" src="{imageHackHac}" /></div>
        <div class="divHackHack"><img class="imageHackHack" src="{imageHackHack}" /></div>
      </div>
    </div>
    <div class="line2">
      <div class="revolutionLine">
        <div class="divHackHackR"><img class="imageHackHackR" src="{imageHackHackR}" /></div>
        <div class="divHackHackRe"><img class="imageHackHackRe" src="{imageHackHackRe}" /></div>
        <div class="divHackHackRev"><img class="imageHackHackRev" src="{imageHackHackRev}" /></div>
        <div class="divHackHackRevo"><img class="imageHackHackRevo" src="{imageHackHackRevo}" /></div>
        <div class="divHackHackRevol"><img class="imageHackHackRevol" src="{imageHackHackRevol}" /></div>
        <div class="divHackHackRevolu"><img class="imageHackHackRevolu" src="{imageHackHackRevolu}" /></div>
        <div class="divHackHackRevolut"><img class="imageHackHackRevolut" src="{imageHackHackRevolut}" /></div>
        <div class="divHackHackRevoluti"><img class="imageHackHackRevoluti" src="{imageHackHackRevoluti}" /></div>
        <div class="divHackHackRevolutio"><img class="imageHackHackRevolutio" src="{imageHackHackRevolutio}" /></div>
        <div class="divHackHackRevolution"><img class="imageHackHackRevolution" src="{imageHackHackRevolution}" /></div>
      </div>
    </div>
  </div>
</div>
