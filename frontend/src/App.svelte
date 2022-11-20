<script lang="ts">
	import Heart from './assets/heart.svelte';

	import { onMount } from 'svelte';
	import Game from './components/game.svelte';
	import classnames from 'classnames';

	const getWords = async (params: { [key: string]: any } = { length: 4, number: 10 }) => {
		const endpoint = new URL('https://random-word-api.herokuapp.com/word');

		Object.entries(params).map(([k, v]) => endpoint.searchParams.append(k, v));

		const response = await fetch(endpoint);
		return (await response.json()) as string[];
	};

	let hasGameEnded = false;
	let words: string[] = [];
	let userIsCorrect = true;

	let finalScore;
	let userName;
	let submittedData = false;

	let userText = '';

	onMount(async () => {
		words = await getWords({ length: 5, number: 15 });
	});

	const submitScore = async () => {
		if (hasGameEnded && !submittedData)
			fetch(new URL('/testscore', 'base_url'), {
				method: 'POST',
				body: JSON.stringify({ name: userName, score: finalScore })
			}).then((req) => {
				if (req.status == 200) submittedData = true;
			});
	};
</script>

{#if !hasGameEnded}
	<Game
		standardRate={0.1}
		invalidRate={0.55}
		onGameEndHandle={() => {
			hasGameEnded = true;
		}}
		onInvalidInputChangeHandle={(n) => {
			userIsCorrect = n;
		}}
		data={words}
		getData={() => getWords({ length: 6, number: 4 })}
		input={userText}
	>
		<div
			class={classnames(
				'my-10 flex h-16 w-11/12 items-center rounded-xl bg-zinc-900 p-2',
				userIsCorrect ? 'shadow-xl shadow-white/10' : 'neon'
			)}
		>
			<input
				bind:value={userText}
				disabled={hasGameEnded}
				placeholder="enter phrase"
				type="text"
				class="h-full w-full rounded-xl bg-black px-3 text-center font-bold outline-none transition-colors duration-300 hover:bg-white/20"
			/>
		</div>
		<div class="mx-auto my-2 text-white/60">
			made with <Heart classes="h-4 inline-block" /> by shitposting ltd
		</div>
	</Game>
{:else}
	<main
		class="flex min-h-screen flex-col items-center justify-center gap-4 bg-black p-10 text-white"
	>
		<p>
			Game is over, please wait for a picture to be taken click the button below to save your
			score restart the game
		</p>
		<input
			class="text-font block rounded-3xl bg-white/20 px-4 py-1 text-center shadow-xl shadow-white/10 outline-none"
			type="text"
			bind:value={userName}
		/>
		<button class="rounded-3xl bg-white/30 px-2 text-white" on:click={submitScore}>
			submit
		</button>
	</main>
{/if}
