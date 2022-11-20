<script lang="ts">
	export let isAccellerated: boolean;
	export let outOfTimeCallback: () => void;
	export let isTyping: boolean;

	let progress = 100;

	let rate = isAccellerated ? 0.999 : 0.9999;

	$: rate = isAccellerated ? 0.999 : 0.9999;

	function step() {
		if (isTyping) progress *= rate;

		if (progress < 0.01) outOfTimeCallback();
		else requestAnimationFrame(step);
	}

	requestAnimationFrame(step);
</script>

<div class="flex w-full flex-1 flex-col items-center justify-center">
	<div class="neon h-3 w-4/5 overflow-hidden rounded-full">
		<div class="h-3 bg-white transition-[width]" style={`width: ${progress}%`} />
	</div>
</div>
