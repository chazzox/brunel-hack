<script lang="ts">
	export let score: number;

	let userName = '';

	const sendWindState = async () => {
		fetch('https://965f-134-83-3-250.eu.ngrok.io/score', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json', 'Access-Control-Allow-Origin': '*' },
			body: JSON.stringify({ name: userName, score })
		});
	};
</script>

<main class="flex min-h-screen flex-col items-center justify-center bg-black p-10 text-white">
	<p>Game is over enter your name and submit to save your score on the leaderboard</p>
	<input
		class="my-3 h-full w-96 rounded-full border-[1px] border-white bg-transparent p-3
    text-center font-bold shadow-lg shadow-white/20 outline-none"
		bind:value={userName}
		type="text"
	/>
	<button on:click={sendWindState}>submit and refresh</button>
</main>
