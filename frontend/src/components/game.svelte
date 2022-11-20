<script lang="ts">
	import classNames from 'classnames';
	import Progress from './progress.svelte';

	export let standardRate: number;
	export let invalidRate: number;
	export let data: string[];
	export let input: string;
	export let getData: () => Promise<typeof data>;
	export let onGameEndHandle: () => void;
	export let onInvalidInputChangeHandle: (arg: boolean) => void;

	let score = 0;
	let isInputValid = true;

	let progress = 100;
	$: if (progress <= 0) hasGameEnded = true;

	let hasGameEnded = false;
	$: if (hasGameEnded) onGameEndHandle();

	let hasGameStarted = false;
	$: if (!hasGameStarted && input) hasGameStarted = true;
	$: if (hasGameStarted) requestAnimationFrame(step);

	let gameRate = invalidRate;
	$: gameRate = isInputValid ? standardRate : invalidRate;

	// subscriptions
	$: onInvalidInputChangeHandle(isInputValid);

	function step() {
		progress = Math.max(0, progress - gameRate);

		if (progress < 0.01) hasGameEnded = true;
		else requestAnimationFrame(step);
	}
</script>

<main
	class={classNames(
		'flex min-h-screen flex-col items-center bg-black p-10 text-white',
		!isInputValid && 'neonIn'
	)}
>
	<div class="mx-auto text-white/80"><p>user score: {score}</p></div>

	<div class="flex flex-1 flex-col items-center justify-center gap-24">
		<p>{data.join(' ')}</p>
	</div>

	<Progress {progress} />

	<slot />
</main>

<style>
	:global(.neon) {
		box-shadow: 0 0 2rem #dc2626, 0 0 0.8rem #dc2626, 0 0 2rem #dc2626;
	}

	:global(.neonIn) {
		box-shadow: 0 0 0.2rem #fff, 0 0 0.2rem #fff, 0 0 2rem #dc2626, 0 0 0.8rem #dc2626,
			0 0 2.8rem #dc2626, inset 0 0 1.3rem #dc2626;
	}
</style>
