<script lang="ts">
	import Heart from './assets/heart.svelte';
	import Logo from "./assets/logo/index.svelte";

	import classnames from 'classnames';

	import { onMount } from 'svelte';

	let words = '';

	let userIsCorrect = true;

	onMount(async () => {
		const response = await fetch(
			'https://random-word-api.herokuapp.com/word?number=10&length=4'
		);
		const wordList = (await response.json()) as string[];
		words = wordList.join(' ');
	});

	$: console.log(words);
</script>

<main class="flex min-h-screen flex-col bg-black px-10 text-white">
	<Logo />

	<div class="flex flex-1 items-center justify-center">
		{#if words.length != 0}
			<p>{words}</p>
		{/if}
	</div>

	<div
		class="my-10 flex h-16 w-full items-center rounded-xl bg-zinc-900 p-2 shadow-xl shadow-white/10"
	>
		<input
			type="text"
			class="h-full w-full rounded-xl bg-black px-3 text-center font-bold outline-none transition-colors duration-300 hover:bg-white/20"
		/>
	</div>
	<div class="mx-auto my-2">made with <Heart classes="h-4 inline-block" /> by shitposting ltd</div
	>
</main>
