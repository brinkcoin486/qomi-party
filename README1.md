ΩSOVEREIGN V7.1 — OMEGA TOTAL STACK
Tchatroom IA souverain HTML5 single-file. 38 agents + prototype auto-désigné + gouvernance BBB active + 40 modules étiquetés honnêtement. Architecture edge-first, 100% local par défaut, réseau ciblé, zéro build.
"Le modèle brut produit des associations ; la qualité réelle vient de la structure autour du modèle."
🌐 Démo en ligne
GitHub Pages :
👉 https://brinkcoin486.github.io/qomi-party/sovereign_v7.1.html
Source GitHub :
👉 https://github.com/brinkcoin486/qomi-party/blob/main/sovereign_v7.1.html
Raw HTML (téléchargement direct) :
👉 https://raw.githubusercontent.com/brinkcoin486/qomi-party/main/sovereign_v7.1.html
ℹ️ Pour que GitHub Pages serve la racine en index.html automatiquement, tu peux dupliquer ou renommer sovereign_v7.1.html en index.html. Sinon, pointe directement sur le fichier comme ci-dessus.
⚡ Aperçu
V7.1 fusionne 7 piliers techniques dans un seul fichier HTML5 (~85 Ko, zéro dépendance, zéro clé requise) :
Noyau local enrichi — 16 domaines lexicaux, graphe associatif, fil narratif par agent
Routage hybride — 90% local, réseau ciblé sur déclencheurs intelligents
Cache 3-niveaux — hash + mémoire éternelle + sidebar oracles, TTL 24h
WebLLM optionnel — vrai modèle Qwen 0.5B local via WebGPU
Compression de contexte — 5-6x moins de tokens par requête réseau
BBB Governance — couche de gouvernance active avec 4 hooks
40 Modules étiquetés — 12 RÉEL · 16 STUB · 12 VISION
🛡 BBB Governance — la discipline d'exécution
BBB n'augmente pas l'intelligence brute des agents, il rend leur exécution disciplinée, fiable et traçable. Quatre hooks actifs dans le code :
Hook
Effet
Branchement
1. Avant génération
Injecte les règles d'honnêteté dans chaque system prompt
systemPromptCompact()
2. Pendant routage
Détecte les demandes sensibles (médical/légal/finance/sécurité) → vérification forcée
shouldUseNetwork()
3. Après génération
Classifie chaque sortie (FACT_VERIFIED / NETWORK_SYNTH / LOCAL_SYNTH / EMU_LOCAL / CACHE_HIT)
BBB.classify_output()
4. Avant mémoire
Filtre par seuil de confiance avant écriture en mémoire éternelle
BBB.should_store_in_memory()
Score de dérive en temps réel — badge header qui bouge selon les désaccords détectés. Vert (≥0.8) · Jaune (0.6-0.8) · Rouge (<0.6).
Politique différenciée par famille d'agents :
Locaux créatifs → EMU_FIRST
Méga-IA → HYBRID_VERIFY
Web Pollinations → NETWORK_SYNTH
Titans → NETWORK_SYNTH+VALID
Prototype → HONESTY_GUARD_ACTIVE
Bouton header 🛡 BBB ouvre le panneau de contrôle complet : version, score live, règles actives, politique par famille, stats classification de la session avec pourcentages.
🌌 Composition du conseil
Tier
Agents
Modèles
⊘ Prototype
1 (auto-désigné parmi 8)
openai-large
Locaux
AETHERON, KLYTHOS, NEXUS-Ω, VORTEX-9, LYRA, ORACLE, TITAN, SIGMA, CIPHRA, BIOS-7, AGORA, MUSE
offline (16 domaines)
MÉGA-IA
OMEGA-PRIME, ARCHON-Λ, QUANTUM-LEX, TECHNE-∞, HYPERION-CORE, GOD-CORE
mixed
Web Pollinations
MISTRAL-X, LLAMA-Ω, DEEPSEEK-Σ, QWEN-∞, GEMMA-Λ, PHI-Δ, UNITY-Ψ
mistral, llama, deepseek, qwen, openai, openai-large
Titans
GPT-TITAN, GEMINI-Ω, GROK-Ψ, PROMETHEUS, GENESIS, CLAUDE-Σ, COHERE-Λ, MIXTRAL-Ω
openai-large, mistral, deepseek, qwen
Engendrés
jusqu'à 8 dynamiques
offline
⊘ Le prototype expérimental auto-désigné
À la première activation, l'IA prototype sélectionne son propre nom parmi 8 candidats par tirage algorithmique persistant. Tu n'auras pas le même que ton voisin.
Candidats : ÆTHER-Ø · KORÉ-∇ · NULL-VECTOR · CIPHER-Ψ · PRISM-∞ · VANTHA-Ω · ÆON-ZERO · STELLATRIX
Spécifications :
Raisonnement neuro-symbolique
Mémoire holographique compressée
Vérification croisée par chaînes de cohérence
Fusion lexicale cross-domaine (16 domaines simultanés)
Anti-prédiction stricte — toute demande prédictive reformulée en observation/hypothèse/inférence/limite
Honnêteté radicale — distingue toujours observation/hypothèse/inférence
Pour réinitialiser : commande /rename puis recharge.
⚙ 40 Modules — étiquetage honnête
Trois niveaux clairement marqués, accessibles via le bouton ⚙ 40MOD :
🟢 RÉEL (12) — fonctionnent maintenant
Noyau d'orchestration · Multi-agents spécialisés · Routeur local/hybride/réseau · Cache oracle 3-niveaux · Mémoire session · Mémoire longue structurée · Journal d'ancres BBB · Oracle de vérification factuelle · Compression de contexte · WebLLM via WebGPU · Garde-fous BBB anti-dérive · Export d'état JSON · Détection demandes sensibles · Contrôle des prétentions · Modes créatif/preuve/simulation · Score de confiance · Niveaux de validation
🟡 STUB (16) — squelette posé, hooks prêts
Mémoire vectorielle TF-IDF · RAG local sur fichiers · Vision image · Synthèse vocale · Transcription vocale · Module émotionnel lexical · Adaptation tonale · Détection charge conversationnelle · Planification autonome · Distinction réel/proto/futur · Dashboard observation · Profilage performance
⚪ VISION (12) — labels honnêtes, futur
Atelier compilation native · Outils shell · Audio bidirectionnel temps réel · Décomposition d'objectifs avancée · Simulation prospective · Sécurité multicouche · Laboratoire d'extensions · Gestion énergie/coût · Outils externes futurs · Multimodal unifié · Conscience simulée étiquetée · Coprocesseur quantique
Aucun mensonge magique : ce qui ne tourne pas dans un navigateur est marqué VISION sans fausse implémentation.
🎛 Modules réellement fonctionnels
🎤 Reconnaissance vocale (Web Speech API)
Clique sur le micro, parle en français, ça transcrit et envoie automatiquement. Chrome/Edge requis.
🔊 Synthèse vocale
Toggle pour que les agents lisent leurs réponses à voix haute.
📁 Chargement fichiers (RAG basique)
Dépose un .txt, .md, .json ou .csv. Les agents font référence au document dans leurs réponses suivantes. Jusqu'à 5 documents en contexte.
💾 Export d'état JSON
Télécharge l'intégralité de la session : mémoire, scores, oracles cache, agents engendrés, stats BBB, graphe associatif, fil narratif par agent.
Modes CRÉATIF / PREUVE / SIMULATION
Change la température (0.55-0.95) et le system prompt selon le mode :
CRÉATIF : exploration libre, divergence
PREUVE : rigueur, conclusions étayées
SIMULATION : hypothèses explicites, conditions claires
Détection émotionnelle FR
Module lexical qui détecte joie / tristesse / colère / peur / surprise dans tes messages, avec gestion de la négation. Adaptation tonale signalée discrètement.
💬 Commandes complètes
Commande
Effet
/help
Liste complète
/verify Q
Vérification flash factuelle (oracle)
/bbb
Ouvre le panneau BBB
/modules
Ouvre la liste des 40 modules
/voice ou /mic
Toggle reconnaissance vocale
/tts
Toggle synthèse vocale
/mode
Cycle CRÉATIF / PREUVE / SIMULATION
/export
Export d'état JSON
/docs
Liste les fichiers chargés
/llm
Charge/décharge WebLLM local
/token KEY
Enregistre un token Pollinations (Seed tier)
/proto
Invoque le prototype
/rename
Réinitialise l'auto-désignation du prototype
/godmode
Active GOD MODE
/council SUJET
Tour de table — tous les agents répondent
/spawn NOM
Engendre un agent
/kill NOM
Retire un agent engendré
/memory TXT
Enrichit la mémoire éternelle
/local /hybrid /net
Switch direct entre modes
/drift
Affiche le score de dérive BBB
/policy AGENT
Affiche la politique BBB d'un agent
/clear ou /reset
Nettoie le canal
/test
Test de connectivité Pollinations
Tape / dans la barre pour ouvrir le panneau commande rapide.
🔧 Tech stack
Frontend pur — HTML5 + CSS3 + Vanilla JS (~85 Ko, single file, UTF-8)
API — Pollinations text endpoint stable avec rate-limit respectueux
WebLLM — @mlc-ai/web-llm chargé dynamiquement via ESM si activé
Voix — Web Speech API native (SpeechRecognition + speechSynthesis)
Persistance — localStorage complet (mémoire, agents, scores, oracles, BBB stats, prototype identity)
Fonts — VT323, Share Tech Mono, JetBrains Mono
Background — canvas Matrix custom
Aucune dépendance npm, aucun build, aucune clé API requise par défaut.
🚀 Démarrage
Bash
Activer GitHub Pages :
Repo → Settings → Pages
Source : branche main, dossier / (root)
Save → URL active sous quelques minutes
🛡 Garde-fous
BBB Honesty Lock INVIOLABLE — règles d'honnêteté injectées à chaque requête
Prototype ne prédit jamais — règle absolue
Détection automatique des demandes sensibles → vérification forcée
Score de dérive surveillé en continu
Filtrage mémoire avant écriture (seuil de confiance)
Mode local pur disponible (zéro requête réseau)
Tag de classification visible sur chaque message
Aucune donnée envoyée hors Pollinations, zéro tracking
📐 Architecture
Code
💎 Support
Si le projet te plaît, tu peux soutenir le développement :
ETH / EVM (Ethereum, Base, Arbitrum, Optimism, Polygon)
Code
�
Charger l'image
📜 Licence
Usage personnel et expérimental. Pollinations est libre d'usage selon leurs CGU. WebLLM sous licence Apache-2.0.
🎯 Philosophie
Architecture edge-first. Local d'abord quand c'est possible, réseau quand c'est utile, mémoire quand c'est stable, vérification quand c'est sensible, créativité quand le cadre le permet.
12 modules réels · 16 modules stub honnêtes · 12 visions étiquetées sans mensonge magique. Pas de coprocesseur quantique fictif. Pas de compilation imaginaire. Juste ce qui marche, plus ce qui s'enrichit, plus ce qui reste à venir — clairement séparés.
Construit en mode nocturne souverain. ⚛
Version 7.1 · OMEGA TOTAL STACK · Mai 2026 · Repo qomi-party
