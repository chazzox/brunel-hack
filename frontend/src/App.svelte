<script lang="ts">
	import Heart from './assets/heart.svelte';
	import classnames from 'classnames';
	import { onMount } from 'svelte';
	import Progress from './components/progress.svelte';
	import { stopTyping } from './utils';

	let words: string[] = [];

	let userIsCorrect = true;

	let userText = '';

	let score = 0;

	let hasUserTypeDebounced = true;

	onMount(async () => {
		const response = await fetch(
			'https://random-word-api.herokuapp.com/word?number=10&length=4'
		);
		words = (await response.json()) as string[];
	});

	$: if (words.length > 0) {
		userIsCorrect = words.join(' ').startsWith(userText);
	}

	$: console.log('user text valid', userIsCorrect);

	$: console.log('user stopped typing', hasUserTypeDebounced);
</script>

<main
	class={classnames(
		'flex min-h-screen flex-col items-center bg-black p-10 text-white',
		!userIsCorrect && 'neonIn'
	)}
>
	<div class="mx-auto text-white/80"><p>user score: {score}</p></div>

	<div class="flex flex-1 flex-col items-center justify-center gap-24">
		{#if words.length != 0}
			<p>{words.join(' ')}</p>
		{/if}
	</div>

	<Progress
		isAccellerated={!userIsCorrect}
		outOfTimeCallback={() => console.log('you ran out of time')}
		isTyping={!hasUserTypeDebounced}
	/>

	<div
		class={classnames(
			'my-10 flex h-16 w-11/12 items-center rounded-xl bg-zinc-900 p-2',
			userIsCorrect ? 'shadow-xl shadow-white/10' : 'neon'
		)}
	>
		<input
			on:keydown={() => {
				hasUserTypeDebounced = false;
			}}
			use:stopTyping
			on:stopTyping={() => {
				hasUserTypeDebounced = true;
			}}
			bind:value={userText}
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

<style>
	:global(.neon) {
		box-shadow: 0 0 2rem #dc2626, 0 0 0.8rem #dc2626, 0 0 2rem #dc2626;
	}

	.neonIn {
		box-shadow: 0 0 0.2rem #fff, 0 0 0.2rem #fff, 0 0 2rem #dc2626, 0 0 0.8rem #dc2626,
			0 0 2.8rem #dc2626, inset 0 0 1.3rem #dc2626;
	}
</style>
