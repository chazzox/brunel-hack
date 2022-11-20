<script lang="ts">
	import Heart from './assets/heart.svelte';
	import Logo from "./assets/logo/index.svelte";

	import Progress from './components/progress.svelte';
	import classnames from 'classnames';
	import { onMount } from 'svelte';

	let userIsCorrect = true;
	let userText = '';

	let hasGameEnded = false;
	let didBeginTyping = false;
	// game state
	let score = 0;
	let progress = 100;
	let words: string[] = [];
	let rate = !userIsCorrect ? 0.35 : 0.1;
	$: rate = !userIsCorrect ? 0.35 : 0.1;

	const getWords = async (params: { [key: string]: any } = { length: 4, number: 10 }) => {
		const endpoint = new URL('https://random-word-api.herokuapp.com/word');

		Object.entries(params).map(([k, v]) => endpoint.searchParams.append(k, v));

		const response = await fetch(endpoint);
		return (await response.json()) as string[];
	};

	onMount(async () => {
		words = await getWords();
	});

	$: if (words.length > 0) {
		userIsCorrect = words.join(' ').startsWith(userText);
		console.log(userIsCorrect, words, userText);
	}
  
	const handleEnterPress = async () => {
		if (!userIsCorrect) {
			// animation shake
			return;
		}
		if (progress <= 0) return;


		// removing words
		const userWords = userText.split(' ');
		let correctCount = userWords.length;

		// checking for partial match of last matching word
		const isLastWordPartial = words[correctCount - 1] != userWords[userWords.length - 1];
		if (isLastWordPartial) correctCount--;

		userText = '';
		words = words.slice(correctCount);
		words = [
			...words,
			...(await getWords({ length: score > 15 ? 10 : 5, number: correctCount }))
		];

		// updating game score
		score += correctCount;

		// add time to timer

		progress = Math.min(100, progress + correctCount * 10);
	};

	const gameOver = () => {
		hasGameEnded = true;
	};

	function step() {
		progress = Math.max(0, progress - rate);

		if (progress < 0.01) gameOver();
		else requestAnimationFrame(step);
	}

	$: if (didBeginTyping) requestAnimationFrame(step);
</script>

{#if !hasGameEnded}
	<main
		class={classnames(
			'flex min-h-screen flex-col items-center bg-black p-10 text-white',
			!userIsCorrect && 'neonIn'
		)}
	>
  	<Logo />
		<div class="mx-auto text-white/80"><p>user score: {score}</p></div>

		<div class="flex flex-1 flex-col items-center justify-center gap-24">
			<p>{words.join(' ')}</p>
		</div>

		<Progress {progress} />

		<div
			class={classnames(
				'my-10 flex h-16 w-11/12 items-center rounded-xl bg-zinc-900 p-2',
				userIsCorrect ? 'shadow-xl shadow-white/10' : 'neon'
			)}
		>
			<input
				on:keydown={(e) => {
					didBeginTyping = true;
					if (e.key == 'Enter') handleEnterPress();
				}}
				bind:value={userText}
				disabled={hasGameEnded}
				placeholder="enter phrase"
				type="text"
				class="h-full w-full rounded-xl bg-black px-3 text-center
	font-bold outline-none transition-colors duration-300 hover:bg-white/20"
			/>
		</div>
		<div class="mx-auto my-2 text-white/60"
			>made with <Heart classes="h-4 inline-block" /> by shitposting ltd</div
		>
	</main>
{:else}
	<main class="flex min-h-screen flex-col items-center justify-center bg-black p-10 text-white">
		oioi
	</main>
{/if}

<style>
	:global(.neon) {
		box-shadow: 0 0 2rem #dc2626, 0 0 0.8rem #dc2626, 0 0 2rem #dc2626;
	}

	.neonIn {
		box-shadow: 0 0 0.2rem #fff, 0 0 0.2rem #fff, 0 0 2rem #dc2626, 0 0 0.8rem #dc2626,
			0 0 2.8rem #dc2626, inset 0 0 1.3rem #dc2626;
	}
</style>
